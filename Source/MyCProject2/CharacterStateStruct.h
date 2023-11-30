// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStateStruct.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FCharacterStateStruct : public  FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// 캐릭터의 기본 고정 스텟
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RecoveryMPValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RecoveryHPValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BaseDamage;
};