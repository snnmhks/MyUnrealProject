// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "MainHUDWidget.h"
#include "MySkillWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "ItemData.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "InventoryIconWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInventoryWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	InventoryHeader->OnPressed.AddDynamic(this, &UInventoryWidget::UIMove);
	InventoryHeader->OnReleased.AddDynamic(this, &UInventoryWidget::UIMoveStop);

	CurrentIndex = 0;
	CanvasSlot = Cast<UCanvasPanelSlot>(InventoryCanvas->Slot);

	for (UWidget* ItemSlot : InventoryPanel->GetAllChildren()) {
		UInventoryIconWidget* tmp = Cast<UInventoryIconWidget>(ItemSlot);
		tmp->ParentInventory = this;
		tmp->Type = ESlotType::SLOT_Inventory;
	}
	
}

void UInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (IsTimer) {
		// ���� ƽ���� �ٽ� ���콺 ��ġ�� �������鼭 ���� ��ġ�κ��� ������ �̵��ߴ����� ����Ͽ� ĵ������ �̵���Ų��.
		CanvasSlot->SetPosition(UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) - MousePos);
	}
}

void UInventoryWidget::UIMove() {
	// ��ư�� ������ �� ���콺 ��ġ�� �����´�.
	MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) - CanvasSlot->GetPosition();
	IsTimer = 1;
}

void UInventoryWidget::UIMoveStop() {
	IsTimer = 0;
}

void UInventoryWidget::SetGoldValue(int _Gold) {
	// FText�� �ٷ� �ٲ� ����� ��� int -> string -> text������ �ٲپ���.
	GoldText->SetText(FText::FromString(FString::FromInt(_Gold)));
}

void UInventoryWidget::SetCrystalValue(int _Gold) {
	CrystalText->SetText(FText::FromString(FString::FromInt(_Gold)));
}

bool UInventoryWidget::AddItemToInventory(UItemData* _Item) {
	if (_Item == nullptr) return false;
	if (CurrentIndex >= 15) return false;

	// �̹� �����ϴ� �������� �߰��� ���
	if (CheckItemList.Contains(_Item->ItemName)) {
		CheckItemList.FindRef(_Item->ItemName)->ItemNumPlus();
		ParentWidget->UI_SkillWidget->QuickSlotItemNumPlus(_Item->ItemName);
	}
	else {
		for (UWidget* ItemSlot : InventoryPanel->GetAllChildren()) {
			UInventoryIconWidget* tmp = Cast<UInventoryIconWidget>(ItemSlot);
			if (tmp->HaveItem->IsInItem == 0) {
				CheckItemList.Add(_Item->ItemName, tmp);
				CheckItemList.FindRef(_Item->ItemName)->SetItemData(_Item);
				break;
			}
		}
	}

	return true;
}

bool UInventoryWidget::UsingItem(FName _ItemName) {
	if (CheckItemList.Contains(_ItemName)) {
		CheckItemList.FindRef(_ItemName)->UsingItem();
		return true;
	}
	return false;
}

FReply UInventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	FEventReply MyReply;
	MyReply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) {
		MyReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}
	else {
		MyReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton);
	}
	UE_LOG(LogTemp, Log, TEXT("Hello"));
	return MyReply.NativeReply;
}
