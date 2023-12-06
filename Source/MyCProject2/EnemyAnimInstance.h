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

public:
	UEnemyAnimInstance();

	UFUNCTION()
		void PlayMongtage(UAnimMontage* _Mongtage);
	// 죽음 몽타주의 끝부분에 도달하면 발생하는 노티파이
	UFUNCTION()
		void AnimNotify_EndDie();
};
