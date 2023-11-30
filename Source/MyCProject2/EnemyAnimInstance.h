// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// ��ȯ ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* SpawnMontage;

public:
	UEnemyAnimInstance();

	UFUNCTION()
		void PlayMongtage(FString Name);
};
