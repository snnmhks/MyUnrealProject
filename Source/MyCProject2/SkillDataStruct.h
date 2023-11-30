// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillDataStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSkillDataStruct : public  FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// ��ų ��Ÿ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float QSkillCoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CSkillCoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MRSkillCoolTime;

	// ��ų ���� �ð� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float QMaxRunTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MRCompleteChargeValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MRMaxChargeValue;
};
