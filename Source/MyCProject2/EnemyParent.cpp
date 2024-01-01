// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyParent.h"
#include "EnemyAnimInstance.h"
#include "EnemyAIController.h"
#include "MyLevelScript.h"
#include "EnemyWidget.h"
#include "ItemData.h"
#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"//CapsuleComponent ����ϱ� ����
#include "Components/WidgetComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h" // GetPlayerController ���

// Sets default values
AEnemyParent::AEnemyParent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �Ž��� ���� ���� ����
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetGenerateOverlapEvents(false);
	GetMesh()->SetNotifyRigidBodyCollision(false);
	GetMesh()->SetCollisionProfileName("EnemyMesh");
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// UI ����
	static ConstructorHelpers::FClassFinder<UEnemyWidget> UI_ENEMYWIDGET(
		TEXT("WidgetBlueprint'/Game/UI/UI_Enemy'"));
	if (UI_ENEMYWIDGET.Succeeded()) {
		UI_EnemyClass = UI_ENEMYWIDGET.Class;
	}

	// Component ����
	EWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("EWidget"));
	EWidget->SetWidgetClass(UI_EnemyClass);
	EWidget->SetCollisionProfileName("NoCollision");
	// �ٸ� ������Ʈ��� �ٸ��� SetUpAttachment�� �ִ�. -> RootComponent�� ���δ�.
	EWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyParent::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnMontage) EnemyAnim->PlayMongtage(SpawnMontage);

	TargetPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	IsDying = false;

	if (EnemyAnim) {
		// ������ �����ϸ� �� ���ʹ� �������.
		EnemyAnim->DieCheck.AddLambda([this]()-> void {
			Destroy();
		});

		// ���� ��Ÿ�ְ� ������ ������ Ʈ���� �۵��Ѵ�.
		EnemyAnim->SpawnCheck.AddLambda([this]()->void {
			Cast<AEnemyAIController>(GetController())->RunBT();
		});

		// ���� Ÿ�ֿ̹� ���� sweep trace�� ����
		EnemyAnim->AttackCheck.AddLambda([this]()->void {
			float AttackRange = 200.0f;
			float AttackRadius = 50.0f;
			FHitResult HitResult;
			FCollisionQueryParams Params(EName::None, false, this);
			bool IsHit = GetWorld()->SweepSingleByChannel(
				HitResult,
				GetActorLocation(),
				GetActorLocation() + GetActorForwardVector() * AttackRange,
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel2,
				FCollisionShape::MakeSphere(AttackRadius),
				Params);
			if (IsHit) {
				AMyCharacter* SweepCharacter = Cast<AMyCharacter>(HitResult.GetActor());
				if (SweepCharacter && !(SweepCharacter->ActionState == "Die")) {
					SweepCharacter->DiffHP(-EnemyDamage);
				}
			}

#if ENABLE_DRAW_DEBUG
			FVector TraceVector = GetActorForwardVector() * AttackRange;
			FVector Center = GetActorLocation() + TraceVector * 0.5f;
			float HalfHeight = AttackRange * 0.5f + AttackRadius;
			FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVector).ToQuat();
			FColor DrawColor = IsHit ? FColor::Green : FColor::Red;
			float DebugTime = 5.0f;

			DrawDebugCapsule(
				GetWorld(),
				Center,
				HalfHeight,
				AttackRadius,
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
			TargetPlayer->GoldDiff(EnemyGold);
			GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
			// ���� �� ������ ������ �����͸� ������ ���´�.
			Cast<AMyLevelScript>(GetWorld()->GetLevelScriptActor())->KilledEnemy();
			ItemData = NewObject<UItemData>();
			SetItemData();
			if (TargetPlayer->GetItem(ItemData)) {

			}
			Cast<AEnemyAIController>(GetController())->StopBT();
			EnemyAnim->StopCurrentMongtage();
			EnemyAnim->PlayMongtage(DieMongtage);
		}
	}
	Cast<UEnemyWidget>(EWidget->GetWidget())->SetHPBarPercent(EnemyCurrentHP, EnemyMaxHP);
}

float AEnemyParent::EnemyAttack() {
	return EnemyAnim->PlayMongtage(AttackMontage1);
}

void AEnemyParent::SetItemData() {
	float tmp = 0.5f;
	if (tmp > FMath::RandRange(0, 1)) {
		ItemData->SetItemData(FName(TEXT("HPPortion")));
	}
	else {
		ItemData->SetItemData(FName(TEXT("MPPortion")));
	}
}