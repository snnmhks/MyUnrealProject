// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

// Ŀ���� ��������Ʈ ��Ƽ ĳ��Ʈ�̹Ƿ� BP�� ��ũ��Ʈ���� ��밡���ϴ�.
DECLARE_MULTICAST_DELEGATE(FOnCheckDelegate);

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// �ִϸ��̼� �ν��Ͻ��� ����� �÷��̾�
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn)
		class AMyCharacter* Player;

	// �޺� ������ �����ϴ� ��������Ʈ
	FOnCheckDelegate OnNextComboCheck; 
	FOnCheckDelegate OnSprintAttackPossible;
	FOnCheckDelegate OnDodgeAttackCheck;
	FOnCheckDelegate OnNoChargeAttackCheck;
	FOnCheckDelegate OnChargeAttackCheck;

	// Ÿ�� ������ �����ϴ� ��������Ʈ
	FOnCheckDelegate OnAttackAble;
	FOnCheckDelegate OnAttackDisable;

	// ����Ʈ�� ��ȯ�ϴ� Ÿ�̹�
	FOnCheckDelegate OnPlayEffect;

	// ���� ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* JumpMontage;

	// �޺� ���� ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ComboMontage;

	// ������Ʈ ���� ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* SprintMontage;

	// ���� ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DodgeMontage;

	// ��� ���� ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* HeavyMontage;
public:
	// ��Ÿ�� ��� �Լ�
	UFUNCTION()
		void PlayMongtage(FString Name);
	// ��Ÿ�� ���ߴ� �Լ�
	UFUNCTION()
		void StopMontage(FString Name);
	// ��Ÿ�� ������ �ѱ�� �Լ���
	UFUNCTION()
		void NextCombo(int _N, FString Name);
	UFUNCTION()
		void JumpToDodgeAttack();
	UFUNCTION()
		void JumpToLanding();
	UFUNCTION()
		void JumpToHeavy1();
	UFUNCTION()
		void JumpToHeavy2();
private:

private:
	UMyAnimInstance();
	virtual void NativeBeginPlay() override;

	// �ִϸ��̼� ��Ƽ����
	// AnimNotify_��Ƽ���� �̸� -> �� ��Ģ�� �ݵ�� ���Ѿ� �Ѵ�.
	// ���� UFUNCTION�� �ٿ���� �Ѵ�. -> ��ũ��Ʈ������ ���� ���� �ƴ� ������ ��ȣ�ۿ��� �ϱ� �����̴�.
	UFUNCTION()
		void AnimNotify_AttackAble();
	UFUNCTION()
		void AnimNotify_AttackDisable();
	UFUNCTION()
		void AnimNotify_DodgeAttackAble();
	UFUNCTION()
		void AnimNotify_DodgeAttackDisable();
	UFUNCTION()
		void AnimNotify_SprintAttackAble();
	UFUNCTION()
		void AnimNotify_SprintAttackDisable();
	UFUNCTION()
		void AnimNotify_HeavyAttackAble();
	UFUNCTION()
		void AnimNotify_HeavyAttackDisable();
	UFUNCTION()
		void AnimNotify_NextCombo();
	UFUNCTION()
		void AnimNotify_SprintAttackPossible();
	UFUNCTION()
		void AnimNotify_DodgeToAttackCheck();
	UFUNCTION()
		void AnimNotify_NoChargeCheck();
	UFUNCTION()
		void AnimNotify_ChargeCheck();
	UFUNCTION()
		void AnimNotify_PlayEffect();
};
