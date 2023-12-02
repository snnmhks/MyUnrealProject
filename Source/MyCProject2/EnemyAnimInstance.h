// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAnimNotifyCheck);

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// º“»Ø ∏˘≈∏¡÷
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* SpawnMontage;

	FOnAnimNotifyCheck DieCheck;

public:
	UEnemyAnimInstance();

	UFUNCTION()
		void PlayMongtage(FString Name);

	UFUNCTION()
		void AnimNotify_EndDie();
};
