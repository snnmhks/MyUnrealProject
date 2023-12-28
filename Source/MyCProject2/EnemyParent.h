// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyParent.generated.h"

UCLASS()
class MYCPROJECT2_API AEnemyParent : public ACharacter
{
	GENERATED_BODY()
private:
	// UI를 받아오는 변수
	TSubclassOf<class UUserWidget> UI_EnemyClass;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* EWidget;
	// 체력바 뒤쪽까지 보여주기
	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* EWidget2;

private:

public:

	// 플레이어
	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* TargetPlayer;

	// 캐릭터에 적용할 애니메이션
	UPROPERTY(VisibleAnywhere)
		class UEnemyAnimInstance* EnemyAnim;

	// 적의 상태 정보
	UPROPERTY(VisibleAnywhere)
		float EnemyMaxHP;
	UPROPERTY(VisibleAnywhere)
		float EnemyCurrentHP;
	UPROPERTY(VisibleAnywhere)
		float EnemyDamage;
	UPROPERTY(VisibleAnywhere)
		int EnemyGold;

	// 죽는 모션 중인가
	UPROPERTY(VisibleAnywhere)
		bool IsDying;

	// 죽는 몽타주
	UPROPERTY(VisibleAnywhere)
		class UAnimMontage* DieMongtage;
	// 소환 몽타주
	UPROPERTY(VisibleAnywhere)
		class UAnimMontage* SpawnMontage;
	// 공격 몽타주
	UPROPERTY(VisibleAnywhere)
		class UAnimMontage* AttackMontage1;

	// 아이템 정보
	UPROPERTY(VisibleAnywhere)
		class UItemData* ItemData;

public:
	// Sets default values for this pawn's properties
	AEnemyParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 데미지를 받으면 호출할 함수
	void OnDamaged(float _Damage);

	// 데미지를 주면 호출할 함수
	float EnemyAttack();

	// 데미지를 주면 호출할 함수
	void SetItemData();
};
