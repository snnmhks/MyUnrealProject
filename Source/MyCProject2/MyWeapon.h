// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"

UCLASS()
class MYCPROJECT2_API AMyWeapon : public AActor
{
	GENERATED_BODY()
private:
	// 무기 매쉬
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* WeaponMesh;
	// 이펙트가 나오는 위치를 선정하기 위한 변수
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* EmitterPoint;
	// 타격시 이펙트
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* HitEffect;
	// 차징 이펙트
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* ChargeEffect;
	// 차징 이펙트2
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* ChargeEffect2;

public:
	// 무기를 들고 있는 캐릭터
	// 캐릭터와 각종 정보를 교환하기 위해여 가져왔다.
	class AMyCharacter* WeoponOwner;

public:	
	// Sets default values for this actor's properties
	AMyWeapon();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayEffect(FName _Name);
	void PlayEffect(FName _Name, FVector SpawnLocation);
};
