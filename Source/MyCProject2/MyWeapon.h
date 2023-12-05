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
	// Ÿ�� ������ ĸ��
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* HitCapsule;
	// Ÿ�ݽ� ����Ʈ
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* HitEffect;

public:
	// ���⸦ ��� �ִ� ĳ����
	// ĳ���Ϳ� ���� ������ ��ȯ�ϱ� ���ؿ� �����Դ�.
	class AMyCharacter* WeoponOwner;

public:	
	// Sets default values for this actor's properties
	AMyWeapon();

	// HitCapsule�� ���� ������ �� ����Ǵ� �Լ�
	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// ��ħ�� ������ ����Ǵ� �Լ�
	UFUNCTION()
		void OnHitEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HitFunction(class AEnemyParent* _Enemy);
};
