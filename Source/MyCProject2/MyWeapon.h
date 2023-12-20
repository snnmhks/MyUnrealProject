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
	// ���� �Ž�
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* WeaponMesh;
	// ����Ʈ�� ������ ��ġ�� �����ϱ� ���� ����
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* EmitterPoint;
	// Ÿ�ݽ� ����Ʈ
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* HitEffect;
	// ��¡ ����Ʈ
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* ChargeEffect;
	// ��¡ ����Ʈ2
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* ChargeEffect2;

public:
	// ���⸦ ��� �ִ� ĳ����
	// ĳ���Ϳ� ���� ������ ��ȯ�ϱ� ���ؿ� �����Դ�.
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
