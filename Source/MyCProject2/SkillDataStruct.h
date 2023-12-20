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

	// 스킬 쿨타임 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float QSkillCoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CSkillCoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MRSkillCoolTime;

	// 스킬 유지 시간 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float QMaxRunTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MRCompleteChargeValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MRMaxChargeValue;

	// 스킬 데미지 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float QSkillDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CSkillDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MRSkillDamage1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MRSkillDamage2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LSkillDamage1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LSkillDamage2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LSkillDamage3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LSkillDamage4;

	// 스킬 범위 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float QSkillRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector QSkillBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CSkillRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector CSkillBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MRSkillRange1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MRSkillBox1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MRSkillRange2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MRSkillBox2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LSkillRange1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector LSkillBox1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LSkillRange2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector LSkillBox2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LSkillRange3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector LSkillBox3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LSkillRange4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector LSkillBox4;
};
