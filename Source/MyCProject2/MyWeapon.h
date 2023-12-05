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
	// 타격 판정용 캡슐
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* HitCapsule;
	// 타격시 이펙트
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* HitEffect;

public:
	// 무기를 들고 있는 캐릭터
	// 캐릭터와 각종 정보를 교환하기 위해여 가져왔다.
	class AMyCharacter* WeoponOwner;

public:	
	// Sets default values for this actor's properties
	AMyWeapon();

	// HitCapsule과 적이 겹쳤을 때 실행되는 함수
	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// 겹침이 끝나면 실행되는 함수
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
