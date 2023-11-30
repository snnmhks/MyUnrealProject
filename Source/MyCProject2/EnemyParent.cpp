// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyParent.h"
#include "EnemyAnimInstance.h"
#include "EnemyAIController.h"

// Sets default values
AEnemyParent::AEnemyParent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 애니메이션 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionProfileName("PhysicsMesh");
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemyParent::BeginPlay()
{
	Super::BeginPlay();
	
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

