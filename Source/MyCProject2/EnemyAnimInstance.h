// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAnimNotifyCheck);

/**
 * 
 */

// 다수의 적 인스턴스가 사용할 애님 인스턴스

UCLASS()
class MYCPROJECT2_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// 죽음 몽타주의 끝부분에 도달하면 발생시킬 델리게이트
	FOnAnimNotifyCheck DieCheck;
	// 스폰 몽타주 마지막을 확인하여 이후 AI컨트롤러를 빙의 시킬 델리게이트
	FOnAnimNotifyCheck SpawnCheck;
	// 공격 타이밍을 확인하여 Sweep Trace를 발생시킬 델리게이트
	FOnAnimNotifyCheck AttackCheck;

	// 지금 재생중인 몽타주
	UPROPERTY(VisibleAnywhere)
		UAnimMontage* CurrentMongtage;

public:
	UEnemyAnimInstance();

	virtual void NativeBeginPlay() override;

	UFUNCTION()
		float PlayMongtage(UAnimMontage* _Mongtage);
	// 지금 재생중인 몽타주를 멈춘다.
	UFUNCTION()
		void StopCurrentMongtage();
	// 죽음 몽타주의 끝부분에 도달하면 발생하는 노티파이
	UFUNCTION()
		void AnimNotify_EndDie();
	UFUNCTION()
		void AnimNotify_SpawnFinish();
	UFUNCTION()
		void AnimNotify_Attacking();
};
