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
		TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/ICE/combat/P_Circle_ChargeUp_Phase2'"));
	if (CHARGE_EFFECT2_MESH.Succeeded()) ChargeEffect2 = CHARGE_EFFECT2_MESH.Object;

	// Component 생성
	HitCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitCapsule"));
	HitCapsule->SetupAttachment(WeaponMesh);
	HitCapsule->SetRelativeLocationAndRotation(FVector(0.0f, -90.0f, 0.0f), FRotator(0.0f, 0.0f, -90.0f));
	HitCapsule->SetCapsuleHalfHeight(90.0f);
	HitCapsule->SetCapsuleRadius(22.0f);
	HitCapsule->SetCollisionProfileName("HittedCapsule");
	HitCapsule->SetGenerateOverlapEvents(true);
	HitCapsule->SetNotifyRigidBodyCollision(false);

}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();
	HitCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMyWeapon::OnHit);
	HitCapsule->OnComponentEndOverlap.AddDynamic(this, &AMyWeapon::OnHitEnd);
}

// Called every frame
void AMyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyWeapon::HitFunction(AEnemyParent* _Enemy) {
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitCapsule->GetComponentLocation() + FVector(0.0f, 0.0f, 70.0f));
	WeoponOwner->IsAttackAble = false;
	_Enemy->OnDamaged(WeoponOwner->DamageValue);
}

void AMyWeapon::PlayEffect(FName _Name) {
	if (_Name == "Charge1") {
		UGameplayStatics::SpawnEmitterAttached(ChargeEffect2, RootComponent, EName::None, FVector(0.0f, -140.0f, 0.0f));
	}
	else if (_Name == "Charge2") {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitCapsule->GetComponentLocation() + FVector(0.0f, 0.0f, 70.0f), FRotator::ZeroRotator, FVector(2.f));
	}

}

void AMyWeapon::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AEnemyParent* Enemy = Cast<AEnemyParent> (OtherActor);
	if (Enemy && WeoponOwner) {
		if (WeoponOwner->IsAttackAble) {
			HitFunction(Enemy);
		}
		else {
			WeoponOwner->IsAttackAble = true;
			WeoponOwner->TargetEnemy = Enemy;
		}
	}
}

void AMyWeapon::OnHitEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	WeoponOwner->IsAttackAble = false;
}