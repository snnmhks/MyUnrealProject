// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDrag.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UItemDrag : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
		class UInventoryIconWidget* DragItem;
	//UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
		//TEnumAsByte<enum ESlotType> Type;
};
