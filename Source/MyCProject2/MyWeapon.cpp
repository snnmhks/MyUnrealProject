// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "Components/CapsuleComponent.h"//CapsuleComponent 사용하기 위해
#include "Components/SkeletalMeshComponent.h" // 스켈레탈 매쉬를 사용하기 위해
#include "Components/PrimitiveComponent.h" 
#include "MyCharacter.h"
#include "EnemyParent.h"
#include "Particles/ParticleSystem.h" // 이펙트를 사용하기 위해
#include "Kismet/GameplayStatics.h" // spawn emitter를 사용하기 위해

// Sets default values
AMyWeapon::AMyWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 무기 매쉬 생성
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WEAPON_MESH(
		TEXT("SkeletalMesh'/Game/ARPG_Pack/ARPG_Halberd/Demo/Weapon/Mesh/Halberd_Mesh.Halberd_Mesh'"));
	if (WEAPON_MESH.Succeeded()) WeaponMesh->SetSkeletalMesh(WEAPON_MESH.Object);
	RootComponent = WeaponMesh;

	EmitterPoint = CreateDefaultSubobject<USceneComponent>(TEXT("EmitterPoint"));
	EmitterPoint->SetRelativeLocation(FVector(0.0f, -120.0f, 0.0f));
	EmitterPoint->SetupAttachment(WeaponMesh);

	// 타격 이펙트 생성
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HIT_EFFECT_MESH(
		TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/Impacts/P_Impact_Enemy_Base'"));
	if (HIT_EFFECT_MESH.Succeeded()) HitEffect = HIT_EFFECT_MESH.Object;

	// 차지 이펙트 생성
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CHARGE_EFFECT_MESH(
		TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/ICE/combat/P_SpearBlast_Pulse'"));
	if (CHARGE_EFFECT_MESH.Succeeded()) ChargeEffect = CHARGE_EFFECT_MESH.Object;

	// 차지 이펙트2 생성
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CHARGE_EFFECT2_MESH(
		TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_Leap/P_Skill_Leap_Base_Charge_Weapon'"));
	if (CHARGE_EFFECT2_MESH.Succeeded()) ChargeEffect2 = CHARGE_EFFECT2_MESH.Object;

}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyWeapon::PlayEffect(FName _Name) {
	if (_Name == "Charge1") {
		UGameplayStatics::SpawnEmitterAttached(ChargeEffect2, EmitterPoint, EName::None, FVector(0.0f), FRotator::ZeroRotator, FVector(1.5f));
	}
	else if (_Name == "Charge2") {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, EmitterPoint->GetComponentLocation(), FRotator::ZeroRotator, FVector(3.f));
	}
}

void AMyWeapon::PlayEffect(FName _Name, FVector SpawnLocation) {
	if (_Name == "Hit") {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, SpawnLocation, FRotator::ZeroRotator, FVector(3.f));
	}
}