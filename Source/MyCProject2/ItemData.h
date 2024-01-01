// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

/**
 * 
 */

UENUM()
enum EItemType {
	ITEM_None			UMETA(DisplayName = "None"),
	ITEM_Useable		UMETA(DisplayName = "Useable"),
	ITEM_Equipment		UMETA(DisplayName = "Equipment")
};

UCLASS()
class MYCPROJECT2_API UItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UItemData();

	UPROPERTY(VisibleAnywhere)
		bool IsInItem;
	UPROPERTY(VisibleAnywhere)
		class UTexture2D* ItemImage;
	UPROPERTY(VisibleAnywhere)
		FName ItemName;
	UPROPERTY(VisibleAnywhere)
		int ItemNum;
	UPROPERTY(VisibleAnywhere)
		class UDataTable* ItemDataTable;
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
		TEnumAsByte<enum EItemType> Type;

public:
	void SetItemData(FName _ItemName);
	void SetItemData(UItemData* _Item);
};
