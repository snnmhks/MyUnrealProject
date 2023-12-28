// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryIconWidget.h"
#include "InventoryWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ItemDrag.h"
#include "ItemData.h"

enum ESlotType;

void UInventoryIconWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	IsInItem = 0;

}

void UInventoryIconWidget::SetItemData() {
	IconImage->SetBrushFromTexture(ItemTexture);
	ItemNum->SetText(FText::FromString(FString::FromInt(ItemNum1)));
	if (IsValid(ParentInventory) && ParentInventory->CheckItemList.Contains(ItemName))
		ParentInventory->CheckItemList.Add(ItemName, this);
}

void UInventoryIconWidget::SetItemData(UItemData* _Item) {
	IsInItem = true;
	ItemTexture = _Item->ItemImage;
	IconImage->SetBrushFromTexture(ItemTexture);
	ItemNum1 = 1;
	ItemNum->SetText(FText::FromString(FString::FromInt(ItemNum1)));
	ItemName = _Item->ItemName;
}

void UInventoryIconWidget::ItemNumPlus() {
	ItemNum1++;
	ItemNum->SetText(FText::FromString(FString::FromInt(ItemNum1)));
}

void UInventoryIconWidget::DeleteItem() {
	if (IsValid(ParentInventory)) ParentInventory->CheckItemList.Remove(ItemName);
	ItemTexture = nullptr;
	IconImage->SetBrushFromTexture(ItemTexture);
	ItemName = EName::None;
	ItemNum->SetText(FText::FromString(FString::FromInt(0)));
}

void UInventoryIconWidget::UsingItem() {
	ItemNum1--;
	if (ItemNum1 <= 0) {
		DeleteItem();
	}
}

void UInventoryIconWidget::SwapItemData(UInventoryIconWidget* MoveItem, UInventoryIconWidget* ThisItem) {
	UInventoryIconWidget* TmpWidget = CreateWidget<UInventoryIconWidget>(GetWorld(), UInventoryIconWidget::StaticClass());
	TmpWidget->IsInItem = MoveItem->IsInItem;
	TmpWidget->ItemNum1 = MoveItem->ItemNum1;
	TmpWidget->ItemTexture = MoveItem->ItemTexture;
	TmpWidget->ItemName = MoveItem->ItemName;
	
	MoveItem->IsInItem = ThisItem->IsInItem;
	MoveItem->ItemNum1 = ThisItem->ItemNum1;
	MoveItem->ItemTexture = ThisItem->ItemTexture;
	MoveItem->ItemName = ThisItem->ItemName;

	ThisItem->IsInItem = TmpWidget->IsInItem;
	ThisItem->ItemNum1 = TmpWidget->ItemNum1;
	ThisItem->ItemTexture = TmpWidget->ItemTexture;
	ThisItem->ItemName = TmpWidget->ItemName;
}

FReply UInventoryIconWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	FEventReply MyReply;
	MyReply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Click"));
	if (IsInItem) {
		MyReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}
	return MyReply.NativeReply;
}

void UInventoryIconWidget::NativeOnDragDetected(const FGeometry& InGeoMetry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) {
	Super::NativeOnDragDetected(InGeoMetry, InMouseEvent, OutOperation);
	if (OutOperation == nullptr) {
		UItemDrag* Oper = NewObject<UItemDrag>();
		OutOperation = Oper;
		Oper->DragItem = this;
		Oper->DefaultDragVisual = this->IconImage; // 드래그 이미지가 OnDrop을 방해한다. 방법이 뭘까
	}
}

bool UInventoryIconWidget::NativeOnDrop(const FGeometry& InGeoMetry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* OutOperation) {
	Super::NativeOnDrop(InGeoMetry, InDragDropEvent, OutOperation);

	UItemDrag* Oper = Cast<UItemDrag>(OutOperation);
	switch (this->Type) {
	case SLOT_Inventory:
		SwapItemData(Oper->DragItem, this);

		this->SetItemData();

		Oper->DragItem->SetItemData();

		return true;
		break;
	case SLOT_Quick:
		this->ItemTexture = Oper->DragItem->ItemTexture;
		this->ItemName = Oper->DragItem->ItemName;
		this->ItemNum1 = Oper->DragItem->ItemNum1;
		this->IsInItem = 1;
		this->SetItemData();
		break;
	}

	return false;
}