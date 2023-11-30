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

	// ĳ������ �⺻ ���� ����
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