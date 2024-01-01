// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"
#include "MySkillWidget.h"
#include "InventoryWidget.h"
#include "InventoryIconWidget.h"
#include "Containers/Queue.h"

void UMainHUDWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	UI_Inventory->ParentWidget = this;
	UI_SkillWidget->ParentWidget = this;
}

void UMainHUDWidget::UsingItemQuickSlot(FName _ItemName) {
	UI_SkillWidget->UsingItem(_ItemName);
}

void UMainHUDWidget::UsingItemInventory(FName _ItemName) {
	UI_Inventory->UsingItem(_ItemName);
}

void UMainHUDWidget::AddToFrontUI(UUserWidget* _AddWidget) {
	UI_Front.Add(_AddWidget);
}

void UMainHUDWidget::RemoveByFrontUI(UUserWidget* _AddWidget) {
	int tmp = UI_Front.Find(_AddWidget);
	if (UI_Front.IsValidIndex(tmp)) UI_Front.RemoveAt(tmp);
}

bool UMainHUDWidget::CloseFrontUI() {
	if (UI_Front.IsValidIndex(0)) {
		UI_Front[0]->SetVisibility(ESlateVisibility::Collapsed);
		UI_Front.RemoveAt(0);
		if (UI_Front.IsEmpty()) return true;
	}
	return false;
}