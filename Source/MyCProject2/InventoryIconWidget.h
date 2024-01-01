// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryIconWidget.generated.h"

/**
 * 
 */
UENUM()
enum ESlotType {
	SLOT_Inventory = 0	UMETA(DisplayName = "Inventory slot"),
	SLOT_Quick			UMETA(DisplayName = "Quick slot")
};

UCLASS()
class MYCPROJECT2_API UInventoryIconWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// �巡�װ� �����Ǹ� �߻��ϴ� �̺�Ʈ
	virtual void NativeOnDragDetected(const FGeometry& InGeoMetry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	// �巡�׸� ������ �߻��ϴ� �̺�Ʈ
	virtual bool NativeOnDrop(const FGeometry& InGeoMetry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* OutOperation) override;

	// ���콺 ��ư ������ �߻��ϴ� �̺�Ʈ
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnInitialized() override;

public:
	class UItemData* HaveItem;
	class UInventoryWidget* ParentInventory;
	class UMySkillWidget* ParentSkill;
	class AMyCharacter* OwnerPlayer;
	// ������ �̹���
	UPROPERTY(meta = (BindWidget))
		class UImage* IconImage;
	// ������ ����
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemNum;
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
		TEnumAsByte<enum ESlotType> Type;

public:

	// ������ ���� ��ȯ
	void SwapItemData(UInventoryIconWidget* MoveItem, UInventoryIconWidget* ThisItem);
	// ������ ���� ����
	void SetItemData();
	void SetItemData(class UItemData* _Item);
	// ������ ���� ���� �߰�
	void ItemNumPlus();
	// ������ ���
	void UsingItem();
	// ������ ����
	void DeleteItem();

};
