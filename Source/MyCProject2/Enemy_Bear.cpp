// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Bear.h"
#include "EnemyAIController.h"
#include "EnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h" // CharacterMovement를 사용하기 위해

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

	// 소환 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SPAWN_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Montage/Spawn.Spawn'"));
	if (SPAWN_MONTAGE.Succeeded()) SpawnMontage = SPAWN_MONTAGE.Object;

	// 공격 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK1_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Montage/Attack'"));
	if (SPAWN_MONTAGE.Succeeded()) AttackMontage1 = ATTACK1_MONTAGE.Object;

	AIControllerClass = AEnemyAIController::StaticClass();

	GetCharacterMovement()->MaxWalkSpeed = 150;
}

void AEnemy_Bear::PostInitializeComponents() {
	Super::PostInitializeComponents();

	EnemyAnim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

void AEnemy_Bear::BeginPlay() {
	Super::BeginPlay();

	EnemyCurrentHP = 100;
	EnemyMaxHP = 100;
	EnemyDamage = 10;
}