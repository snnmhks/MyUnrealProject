// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Spider.h"
#include "EnemyAIController.h"
#include "EnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h" // CharacterMovement를 사용하기 위해

AEnemy_Spider::AEnemy_Spider() {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(
		TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Great_Spider/SK_Greater_Spider'"));
	if (CharacterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ENEMY_ANIM(
		TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Great_Spider/ABP/ABP_Spider'"));
	if (ENEMY_ANIM.Succeeded()) GetMesh()->SetAnimInstanceClass(ENEMY_ANIM.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DIE_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Great_Spider/Mongtage/Die'"));
	if (DIE_MONTAGE.Succeeded()) DieMongtage = DIE_MONTAGE.Object;

	// 소환 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SPAWN_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Great_Spider/Mongtage/Spawn'"));
	if (SPAWN_MONTAGE.Succeeded()) SpawnMontage = SPAWN_MONTAGE.Object;

	// 공격 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK1_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Great_Spider/Mongtage/Attack'"));
	if (SPAWN_MONTAGE.Succeeded()) AttackMontage1 = ATTACK1_MONTAGE.Object;

	AIControllerClass = AEnemyAIController::StaticClass();

	GetCharacterMovement()->MaxWalkSpeed = 250;
}

void AEnemy_Spider::PostInitializeComponents() {
	Super::PostInitializeComponents();

	EnemyAnim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

void AEnemy_Spider::BeginPlay() {
	Super::BeginPlay();

	EnemyMaxHP = 80;
	EnemyCurrentHP = EnemyMaxHP;
	EnemyDamage = 8;
	EnemyGold = 20;
	AttackSpeed = 1.5f;
}