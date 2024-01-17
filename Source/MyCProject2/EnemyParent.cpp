// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyParent.h"
#include "EnemyAnimInstance.h"
#include "EnemyAIController.h"
#include "MyLevelScript.h"
#include "EnemyWidget.h"
#include "ItemData.h"
#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"//CapsuleComponent 사용하기 위해
#include "Components/WidgetComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h" // GetPlayerController 사용

// Sets default values
AEnemyParent::AEnemyParent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 매쉬의 각종 정보 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetGenerateOverlapEvents(false);
	GetMesh()->SetNotifyRigidBodyCollision(false);
	GetMesh()->SetCollisionProfileName("EnemyMesh");
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// UI 생성
	static ConstructorHelpers::FClassFinder<UEnemyWidget> UI_ENEMYWIDGET(
		TEXT("WidgetBlueprint'/Game/UI/UI_Enemy'"));
	if (UI_ENEMYWIDGET.Succeeded()) {
		UI_EnemyClass = UI_ENEMYWIDGET.Class;
	}

	// Component 생성
	EWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("EWidget"));
	EWidget->SetWidgetClass(UI_EnemyClass);
	EWidget->SetCollisionProfileName("NoCollision");
	// 다른 컴포넌트들과 다르게 SetUpAttachment만 있다. -> RootComponent에 붙인다.
	EWidget->SetupAttachment(RootComponent);

	AttackSpeed = 1.0f;
	AttackRange = 200.0f;
	LDAttackRange = 0.0f;
	AttackRadius = 50.0f;

	AddGiveGold = 1.0f;
}

// Called when the game starts or when spawned
void AEnemyParent::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnMontage) EnemyAnim->PlayMongtage(SpawnMontage);

	TargetPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	IsDying = false;

	if (EnemyAnim) {
		// 죽음에 도달하면 이 엑터는 사라진다.
		EnemyAnim->DieCheck.AddLambda([this]()-> void {
			EnemyAnim->Montage_Pause(DieMongtage);
			GetWorldTimerManager().SetTimer(DieTimerHandle, this, &AEnemyParent::Diying, 1, false, 1);
		});

		// 스폰 몽타주가 끝나면 비헤비어 트리를 작동한다.
		EnemyAnim->SpawnCheck.AddLambda([this]()->void {
			Cast<AEnemyAIController>(GetController())->RunBT();
		});

		// 공격 타이밍에 맞춰 sweep trace를 실행
		EnemyAnim->AttackCheck.AddLambda([this]()->void {
			PlayEffect();
			float ARange = 0.0f;
			float ARadius = 0.0f;
			switch (AS) {
			case Basic_Attack:
				ARange = AttackRange;
				ARadius = AttackRadius;
				break;
			case LD_Attack:
				ARange = LDAttackRange;
				ARadius = LDAttackRadius;
			}
			FHitResult HitResult;
			FCollisionQueryParams Params(EName::None, false, this);
			bool IsHit = GetWorld()->SweepSingleByChannel(
				HitResult,
				GetActorLocation(),
				GetActorLocation() + GetActorForwardVector() * ARange,
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel2,
				FCollisionShape::MakeSphere(ARadius),
				Params);
			if (IsHit) {
				AMyCharacter* SweepCharacter = Cast<AMyCharacter>(HitResult.GetActor());
				if (SweepCharacter && !(SweepCharacter->ActionState == static_cast<int>(EActionState::STATE_Die))) {
					PlayHittedEffect(HitResult.ImpactPoint);
					SweepCharacter->DiffHP(-EnemyDamage);
				}
			}

#if ENABLE_DRAW_DEBUG
			FVector TraceVector = GetActorForwardVector() * ARange;
			FVector Center = GetActorLocation() + TraceVector * 0.5f;
			float HalfHeight = ARange * 0.5f + ARadius;
			FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVector).ToQuat();
			FColor DrawColor = IsHit ? FColor::Green : FColor::Red;
			float DebugTime = 5.0f;

			DrawDebugCapsule(
				GetWorld(),
				Center,
				HalfHeight,
				ARadius,
				CapsuleRot,
				DrawColor,
				false,
				DebugTime
				);
#endif
		});
	}

}

// Called every frame
void AEnemyParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator TargetRotation = TargetPlayer->GetActorRotation();
	EWidget->SetWorldRotation(TargetRotation + FRotator(0.0f, 180.0f, 0.0f));

}

// Called to bind functionality to input
void AEnemyParent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyParent::OnDamaged(float _Damage) {
	if (IsDying) return;
	EnemyCurrentHP -= _Damage;
	if (EnemyCurrentHP <= 0) {
		IsDying = true;
		EnemyCurrentHP = 0;
		if (DieMongtage && EnemyAnim) {
			GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
			// 죽을 때 선물할 아이템 데이터를 생성해 놓는다.
			Cast<AMyLevelScript>(GetWorld()->GetLevelScriptActor())->KilledEnemy();
			ItemData = NewObject<UItemData>();
			if (SetItemData()) TargetPlayer->GetItem(ItemData);
			GiveCrystal();
			GiveGold();
			Cast<AEnemyAIController>(GetController())->StopBT();
			EnemyAnim->StopCurrentMongtage();
			EnemyAnim->PlayMongtage(DieMongtage);
		}
	}
	Cast<UEnemyWidget>(EWidget->GetWidget())->SetHPBarPercent(EnemyCurrentHP, EnemyMaxHP);
}

float AEnemyParent::EnemyAttack() {
	if (!IsValid(AttackMontage1)) return 0.0f;
	AS = Basic_Attack;
	return EnemyAnim->Montage_Play(AttackMontage1, AttackSpeed);
}

float AEnemyParent::EnemyLDAttack() {
	if (!IsValid(LDAttackMontage1)) return 0.0f;
	AS = LD_Attack;
	return EnemyAnim->Montage_Play(LDAttackMontage1, AttackSpeed);
}

bool AEnemyParent::SetItemData() {
	int tmp = 100;
	if (tmp > FMath::RandRange(0, 100)) {
		ItemData->SetItemData(FName(TEXT("HPPortion")));
		return true;
	}
	if (tmp > FMath::RandRange(0, 100)) {
		ItemData->SetItemData(FName(TEXT("MPPortion")));
		return true;
	}
	return false;
}

void AEnemyParent::GiveGold() {
	if (30 > FMath::RandRange(0, 100)) {
		TargetPlayer->GoldDiff(EnemyGold * AddGiveGold);
	}
}

void AEnemyParent::GiveCrystal() {
	if (1 > FMath::RandRange(0, 100)) {
		TargetPlayer->CrystalDiff(1);
	}
}

void AEnemyParent::Diying() {
	GetWorldTimerManager().ClearTimer(DieTimerHandle);
	Destroy();
}

void AEnemyParent::PlayEffect() {}

void AEnemyParent::PlayHittedEffect(FVector SpawnLocation) {}