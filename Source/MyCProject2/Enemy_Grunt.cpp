// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Grunt.h"
#include "EnemyAIController.h"
#include "EnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h" // CharacterMovement를 사용하기 위해
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystem.h" // 이펙트를 사용하기 위해
#include "Kismet/GameplayStatics.h" // spawn emitter를 사용하기 위해

AEnemy_Grunt::AEnemy_Grunt() {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(
		TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Master_Grunt/SK_Master_Grunt'"));
	if (CharacterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ENEMY_ANIM(
		TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Master_Grunt/ABP/ABP_Grunt'"));
	if (ENEMY_ANIM.Succeeded()) GetMesh()->SetAnimInstanceClass(ENEMY_ANIM.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DIE_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Master_Grunt/Montage/Die'"));
	if (DIE_MONTAGE.Succeeded()) DieMongtage = DIE_MONTAGE.Object;

	// 소환 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SPAWN_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Master_Grunt/Montage/Spawn'"));
	if (SPAWN_MONTAGE.Succeeded()) SpawnMontage = SPAWN_MONTAGE.Object;

	// 공격 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK1_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Master_Grunt/Montage/Attack'"));
	if (ATTACK1_MONTAGE.Succeeded()) AttackMontage1 = ATTACK1_MONTAGE.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LDATTACK_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Master_Grunt/Montage/Attack2'"));
	if (LDATTACK_MONTAGE.Succeeded()) LDAttackMontage1 = LDATTACK_MONTAGE.Object;

	// 타격 이펙트 생성
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HIT_EFFECT_MESH(
		TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_SpiderBoss/Impact/P_Charge_Swing_01_Fire'"));
	if (HIT_EFFECT_MESH.Succeeded()) LDAttackEffect = HIT_EFFECT_MESH.Object;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HITTED_EFFECT_MESH(
		TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Gruntling/Bomber/P_FireBombExplosion'"));
	if (HITTED_EFFECT_MESH.Succeeded()) HittedEffect = HITTED_EFFECT_MESH.Object;

	AIControllerClass = AEnemyAIController::StaticClass();

	GetCharacterMovement()->MaxWalkSpeed = 150;

	EWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
}

void AEnemy_Grunt::PostInitializeComponents() {
	Super::PostInitializeComponents();

	EnemyAnim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

void AEnemy_Grunt::BeginPlay() {
	Super::BeginPlay();

	EnemyMaxHP = 200;
	EnemyCurrentHP = EnemyMaxHP;
	EnemyDamage = 20;
	EnemyLDDamage = 40;
	EnemyGold = 50;
	AttackSpeed = 1.5f;
	LDAttackSpeed = 1.0f;
	AttackRange = 200.0f;
	AttackRadius = 50.0f;
	LDAttackRange = 800.0f;
	LDAttackRadius = 60.0f;
}

void AEnemy_Grunt::PlayEffect() {
	if (AS == EAttackState::LD_Attack) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LDAttackEffect,
			GetActorLocation() + GetActorForwardVector() * 100,
			FRotator::ZeroRotator, FVector(1.f));
	}
}

void AEnemy_Grunt::PlayHittedEffect(FVector SpawnLocation) {
	if (AS == EAttackState::LD_Attack) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HittedEffect,
			SpawnLocation,
			FRotator::ZeroRotator, FVector(1.f));
	}
}