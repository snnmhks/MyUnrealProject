// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"
#include "MySkillWidget.h"
#include "InventoryWidget.h"
#include "InventoryIconWidget.h"

void UMainHUDWidget::UsingItem(FName _ItemName) {
	UI_Inventory->UsingItem(_ItemName);
	UI_SkillWidget->UsingItem(_ItemName);
}