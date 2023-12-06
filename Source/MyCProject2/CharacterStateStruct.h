// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStateStruct.generated.h"

/**
 *
 */

// USTRUCT로 만들고 엔진 내 DataTable을 사용해야하니 블루프린트 타입까지 써놔야한다.
// FTableRowBase를 상속받아 DataTable을 사용할 수 있게 한다.

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