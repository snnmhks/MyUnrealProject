// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Wolf.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "EnemyAnimInstance.h"

AEnemy_Wolf::AEnemy_Wolf() {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(
		TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Wolf/SK_Enemy_Wolf_Base'"));
	if (CharacterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ENEMY_ANIM(
		TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Wolf/ABP/ABP_Wolf'"));
	if (ENEMY_ANIM.Succeeded()) GetMesh()->SetAnimInstanceClass(ENEMY_ANIM.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DIE_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Wolf/Montage/Die'"));
	if (DIE_MONTAGE.Succeeded()) DieMongtage = DIE_MONTAGE.Object;

	// 家券 根鸥林 积己
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SPAWN_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Wolf/Montage/Spawn'"));
	if (SPAWN_MONTAGE.Succeeded()) SpawnMontage = SPAWN_MONTAGE.Object;

	// 傍拜 根鸥林 积己
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK1_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Wolf/Montage/Attack'"));
	if (ATTACK1_MONTAGE.Succeeded()) AttackMontage1 = ATTACK1_MONTAGE.Object;

	AIControllerClass = AEnemyAIController::StaticClass();
}

void AEnemy_Wolf::PostInitializeComponents() {
	Super::PostInitializeComponents();

	EnemyAnim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

void AEnemy_Wolf::BeginPlay() {
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = 150;
	EnemyMaxHP = 50;
	EnemyCurrentHP = EnemyMaxHP;
	EnemyDamage = 5;
	EnemyGold = 20;
	AttackSpeed = 1.0f;
	AttackRange = 150.0f;
	AttackRadius = 50.0f;
}