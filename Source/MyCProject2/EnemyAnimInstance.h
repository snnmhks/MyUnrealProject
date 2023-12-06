// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAnimNotifyCheck);

/**
 * 
 */

// �ټ��� �� �ν��Ͻ��� ����� �ִ� �ν��Ͻ�

UCLASS()
class MYCPROJECT2_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// ���� ��Ÿ���� ���κп� �����ϸ� �߻���ų ��������Ʈ
	FOnAnimNotifyCheck DieCheck;

public:
	UEnemyAnimInstance();

	UFUNCTION()
		void PlayMongtage(UAnimMontage* _Mongtage);
	// ���� ��Ÿ���� ���κп� �����ϸ� �߻��ϴ� ��Ƽ����
	UFUNCTION()
		void AnimNotify_EndDie();
};
