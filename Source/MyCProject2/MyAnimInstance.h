// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

// 커스텀 델리게이트 멀티 캐스트이므로 BP나 스크립트에서 사용가능하다.
DECLARE_MULTICAST_DELEGATE(FOnCheckDelegate);

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// 애니메이션 인스턴스와 연결된 플레이어
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn)
		class AMyCharacter* Player;

	// 콤보 유지를 감지하는 델리게이트
	FOnCheckDelegate OnNextComboCheck; 
	FOnCheckDelegate OnSprintAttackPossible;
	FOnCheckDelegate OnDodgeAttackCheck;
	FOnCheckDelegate OnNoChargeAttackCheck;
	FOnCheckDelegate OnChargeAttackCheck;

	// 타격 유무를 감지하는 델리게이트
	FOnCheckDelegate OnAttackAble;
	FOnCheckDelegate OnAttackDisable;

	// 이펙트를 소환하는 타이밍
	FOnCheckDelegate OnPlayEffect;

	// 점프 몽타주
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* JumpMontage;

	// 콤보 공격 몽타주
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ComboMontage;

	// 스프린트 공격 몽타주
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* SprintMontage;

	// 닷지 몽타주
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DodgeMontage;

	// 헤비 어택 몽타주
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* HeavyMontage;
public:
	// 몽타주 재생 함수
	UFUNCTION()
		void PlayMongtage(FString Name);
	// 몽타주 멈추는 함수
	UFUNCTION()
		void StopMontage(FString Name);
	// 몽타주 섹션을 넘기는 함수들
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

	// 애니메이션 노티파이
	// AnimNotify_노티파이 이름 -> 이 규칙을 반드시 지켜야 한다.
	// 또한 UFUNCTION을 붙여줘야 한다. -> 스크립트에서만 쓰는 것이 아닌 엔진과 상호작용을 하기 때문이다.
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
