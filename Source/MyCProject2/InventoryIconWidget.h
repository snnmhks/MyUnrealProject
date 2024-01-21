// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryIconWidget.generated.h"

/**
 * 
 */
enum class ESlotType : uint8 {
	SLOT_Inventory		UMETA(DisplayName = "Inventory slot"),
	SLOT_Quick			UMETA(DisplayName = "Quick slot")
};

UCLASS()
class MYCPROJECT2_API UInventoryIconWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// 드래그가 감지되면 발생하는 이벤트
	virtual void NativeOnDragDetected(const FGeometry& InGeoMetry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	// 드래그를 놓으면 발생하는 이벤트
	virtual bool NativeOnDrop(const FGeometry& InGeoMetry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* OutOperation) override;

	// 마우스 버튼 눌리면 발생하는 이벤트
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY()
		class UItemData* HaveItem;
	UPROPERTY()
		class UInventoryWidget* ParentInventory;
	UPROPERTY()
		class UMySkillWidget* ParentSkill;
	// 아이콘 이미지
	UPROPERTY(meta = (BindWidget))
		class UImage* IconImage;
	// 아이템 갯수
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemNum;
	enum ESlotType Type;

public:

	// 아이템 정보 교환
	void SwapItemData(UInventoryIconWidget* MoveItem, UInventoryIconWidget* ThisItem);
	// 아이템 정보 셋팅
	void SetItemData();
	void SetItemData(class UItemData* _Item);
	// 아이템 소유 갯수 추가
	void ItemNumPlus();
	// 아이템 사용
	void UsingItem();
	// 아이템 삭제
	void DeleteItem();

};
