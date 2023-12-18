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
	// ���� ��Ÿ�� �������� Ȯ���Ͽ� ���� AI��Ʈ�ѷ��� ���� ��ų ��������Ʈ
	FOnAnimNotifyCheck SpawnCheck;
	// ���� Ÿ�̹��� Ȯ���Ͽ� Sweep Trace�� �߻���ų ��������Ʈ
	FOnAnimNotifyCheck AttackCheck;

	// ���� ������� ��Ÿ��
	UPROPERTY(VisibleAnywhere)
		UAnimMontage* CurrentMongtage;

public:
	UEnemyAnimInstance();

	virtual void NativeBeginPlay() override;

	UFUNCTION()
		float PlayMongtage(UAnimMontage* _Mongtage);
	// ���� ������� ��Ÿ�ָ� �����.
	UFUNCTION()
		void StopCurrentMongtage();
	// ���� ��Ÿ���� ���κп� �����ϸ� �߻��ϴ� ��Ƽ����
	UFUNCTION()
		void AnimNotify_EndDie();
	UFUNCTION()
		void AnimNotify_SpawnFinish();
	UFUNCTION()
		void AnimNotify_Attacking();
};
