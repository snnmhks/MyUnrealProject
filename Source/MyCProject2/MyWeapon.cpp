// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "Components/CapsuleComponent.h"//CapsuleComponent 사용하기 위해
#include "Components/SkeletalMeshComponent.h" // 스켈레탈 매쉬를 사용하기 위해
#include "Components/PrimitiveComponent.h" 
#include "MyCharacter.h"
#include "EnemyParent.h"

// Sets default values
AMyWeapon::AMyWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 캐릭터 매쉬 생성
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WEAPON_MESH(
		TEXT("SkeletalMesh'/Game/ARPG_Pack/ARPG_Halberd/Demo/Weapon/Mesh/Halberd_Mesh.Halberd_Mesh'"));
	if (WEAPON_MESH.Succeeded()) WeaponMesh->SetSkeletalMesh(WEAPON_MESH.Object);
	RootComponent = WeaponMesh;

	// Component 생성
	HitCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitCapsule"));
	HitCapsule->SetupAttachment(WeaponMesh);
	HitCapsule->SetRelativeLocationAndRotation(FVector(0.0f, -90.0f, 0.0f), FRotator(0.0f, 0.0f, -90.0f));
	HitCapsule->SetCapsuleHalfHeight(90.0f);
	HitCapsule->SetCapsuleRadius(22.0f);
	HitCapsule->SetCollisionProfileName("HittedCapsule");
	HitCapsule->SetGenerateOverlapEvents(true);
	HitCapsule->SetNotifyRigidBodyCollision(false);
	HitCapsule->SetHiddenInGame(false);

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

void AMyWeapon::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AEnemyParent* Enemy = Cast<AEnemyParent> (OtherActor);
	if (Enemy && WeoponOwner) {
		UE_LOG(LogTemp, Log, TEXT("Overlap"));
		if (WeoponOwner->IsAttackAble) {
			WeoponOwner->IsAttackAble = false;
			UE_LOG(LogTemp, Log, TEXT("Hit"));
			// 타격 후 뭘 할 지 작성
		}
		else {
			WeoponOwner->IsAttackAble = true;
		}
	}
}

void AMyWeapon::OnHitEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	WeoponOwner->IsAttackAble = false;
}