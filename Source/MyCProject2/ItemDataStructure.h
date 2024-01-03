// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructure.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EItemType {
	ITEM_None = 0		UMETA(DisplayName = "None"),
	ITEM_Useable		UMETA(DisplayName = "Useable"),
	ITEM_Equipment		UMETA(DisplayName = "Equipment")
};

USTRUCT(BlueprintType)
struct FItemDataStructure : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemName;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		TEnumAsByte<enum EItemType> Type;
};
