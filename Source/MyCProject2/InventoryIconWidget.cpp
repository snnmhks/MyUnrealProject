// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryIconWidget.h"
#include "InventoryWidget.h"
#include "MySkillWidget.h"
#include "MainHUDWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "ItemDrag.h"
#include "ItemData.h"

enum ESlotType;

void UInventoryIconWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	HaveItem = NewObject<UItemData>();
	OwnerPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

void UInventoryIconWidget::SetItemData() {
	IconImage->SetBrushFromTexture(HaveItem->ItemImage);
	ItemNum->SetText(FText::FromString(FString::FromInt(HaveItem->ItemNum)));
	if (IsValid(ParentInventory) && ParentInventory->CheckItemList.Contains(HaveItem->ItemName))
		ParentInventory->CheckItemList.Add(HaveItem->ItemName, this);
}

void UInventoryIconWidget::SetItemData(UItemData* _Item) {
	HaveItem->SetItemData(_Item);
	IconImage->SetBrushFromTexture(HaveItem->ItemImage);
	ItemNum->SetText(FText::FromString(FString::FromInt(HaveItem->ItemNum)));
}

void UInventoryIconWidget::ItemNumPlus() {
	HaveItem->ItemNum++;
	ItemNum->SetText(FText::FromString(FString::FromInt(HaveItem->ItemNum)));
}

void UInventoryIconWidget::DeleteItem() {
	if (IsValid(ParentInventory)) ParentInventory->CheckItemList.Remove(HaveItem->ItemName);
	UItemData* tmp = NewObject<UItemData>();
	HaveItem->SetItemData(tmp);
	IconImage->SetBrushFromTexture(HaveItem->ItemImage);
	ItemNum->SetText(FText::FromString(FString::FromInt(0)));
}

void UInventoryIconWidget::UsingItem() {
	if (HaveItem->Type != EItemType::ITEM_Useable) return;
	if (HaveItem->ItemName == "HPPortion") {
		OwnerPlayer->DiffHP(50);
	}
	else if (HaveItem->ItemName == "MPPortion") {
		OwnerPlayer->DiffMP(50);
	}
	HaveItem->ItemNum--;
	ItemNum->SetText(FText::FromString(FString::FromInt(HaveItem->ItemNum)));
	if (HaveItem->ItemNum <= 0) {
		DeleteItem();
	}
}

void UInventoryIconWidget::SwapItemData(UInventoryIconWidget* MoveItem, UInventoryIconWidget* ThisItem) {
	UItemData* tmp = NewObject<UItemData>();
	tmp->SetItemData(MoveItem->HaveItem);
	MoveItem->HaveItem->SetItemData(ThisItem->HaveItem);
	ThisItem->HaveItem->SetItemData(tmp);
}

FReply UInventoryIconWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	FEventReply MyReply;
	MyReply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Click"));
	if (HaveItem->IsInItem) {
		if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) {
			MyReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		}
		else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton)) {
			switch (Type) {
			case SLOT_Inventory:
				ParentInventory->ParentWidget->UsingItemQuickSlot(HaveItem->ItemName);
				break;
			case SLOT_Quick:
				ParentSkill->ParentWidget->UsingItemInventory(HaveItem->ItemName);
				break;
			}
			UsingItem();
		}
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
		UE_LOG(LogTemp, Log, TEXT("%d"), this->HaveItem->Type);
		if (this->HaveItem->Type == ITEM_Useable) {
			this->HaveItem->SetItemData(Oper->DragItem->HaveItem);
			this->SetItemData();
		}
		break;
	}

	return false;
}