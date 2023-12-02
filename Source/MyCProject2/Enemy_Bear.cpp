// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Bear.h"
#include "EnemyAIController.h"
#include "EnemyAnimInstance.h"

AEnemy_Bear::AEnemy_Bear() {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(
		TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Enemy_Bear'"));
	if (CharacterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ENEMY_ANIM(
		TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/ABP/ABP_Bear'"));
	if (ENEMY_ANIM.Succeeded()) GetMesh()->SetAnimInstanceClass(ENEMY_ANIM.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BEAR_DIE_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Montage/Die'"));
	if (BEAR_DIE_MONTAGE.Succeeded()) DieMongtage = BEAR_DIE_MONTAGE.Object;

	AIControllerClass = AEnemyAIController::StaticClass();
}

void AEnemy_Bear::PostInitializeComponents() {
	Super::PostInitializeComponents();

	EnemyAnim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

void AEnemy_Bear::BeginPlay() {
	Super::BeginPlay();

	EnemyCurrentHP = 100;
	EnemyMaxHP = 100;
}