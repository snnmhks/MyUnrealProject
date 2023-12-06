// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyParent.h"
#include "EnemyAnimInstance.h"
#include "EnemyAIController.h"
#include "EnemyWidget.h"
#include "MyWeapon.h"
#include "Components/WidgetComponent.h"

// Sets default values
AEnemyParent::AEnemyParent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 매쉬의 각종 정보 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetNotifyRigidBodyCollision(false);
	GetMesh()->SetCollisionProfileName("PhysicsMesh");
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
	EWidget2 = CreateDefaultSubobject<UWidgetComponent>(TEXT("EWidget2"));
	EWidget->SetWidgetClass(UI_EnemyClass);
	EWidget2->SetWidgetClass(UI_EnemyClass);
	EWidget->SetCollisionProfileName("NoCollision");
	EWidget2->SetCollisionProfileName("NoCollision");
	EWidget2->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	// 다른 컴포넌트들과 다르게 SetUpAttachment만 있다 -> RootComponent에 붙인다.
	EWidget->SetupAttachment(RootComponent);
	EWidget2->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyParent::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnMontage) EnemyAnim->PlayMongtage(SpawnMontage);

	IsDying = false;

	if (EnemyAnim) {
		// 죽음에 도달하면 이 엑터는 사라진다.
		EnemyAnim->DieCheck.AddLambda([this]()-> void {
			IsDying = false;
			Destroy();
		});
	}

}

// Called every frame
void AEnemyParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
			EnemyAnim->PlayMongtage(DieMongtage);
		}
	}
	Cast<UEnemyWidget>(EWidget->GetWidget())->SetHPBarPercent(EnemyCurrentHP, EnemyMaxHP);
	Cast<UEnemyWidget>(EWidget2->GetWidget())->SetHPBarPercent(EnemyCurrentHP, EnemyMaxHP);
}
