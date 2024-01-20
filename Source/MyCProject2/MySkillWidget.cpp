// Fill out your copyright notice in the Description page of Project Settings.

#include "MySkillWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Fonts/SlateFontInfo.h"
#include "Components/UniformGridPanel.h"
#include "InventoryIconWidget.h"
#include "ItemData.h"

#define LOCTEXT_NAMESPACE "MyNameSpace"

void UMySkillWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	for (UWidget* ItemSlot : QuickSlotPanel->GetAllChildren()) {
		UInventoryIconWidget* tmp = Cast<UInventoryIconWidget>(ItemSlot);
		tmp->ParentSkill = this;
		tmp->Type = ESlotType::SLOT_Quick;
	}
}

void UMySkillWidget::ChargeBarActivate(FName Name) {
	ChargeBar->SetPercent(0.f);
	ChargeBar->SetVisibility(ESlateVisibility::Visible);
	if (Name == "MR") {
		//ChargeBarText->SetText(FText::Format(LOCTEXT("Attack","Heavy Attack")));
	}
	else if (Name == "Q") {
		//ChargeBarText->SetText(FText::Format(LOCTEXT("Attack", "Sprinting")));
	}
}

void UMySkillWidget::ChargeBarDisable() {
	ChargeBar->SetVisibility(ESlateVisibility::Hidden);
}

void UMySkillWidget::MLActivate() {
	MLSkill->SetVisibility(ESlateVisibility::Visible);
	MLText->SetVisibility(ESlateVisibility::Visible);
}

void UMySkillWidget::MLDisable() {
	MLSkill->SetVisibility(ESlateVisibility::Hidden);
	MLText->SetVisibility(ESlateVisibility::Hidden);
}

void UMySkillWidget::IconSizeDown(FName Name) {
	if (Name == "Q") {
		Cast<UCanvasPanelSlot>(QSkill->Slot.Get())->SetSize(FVector2D(60, 60));
	}
	else if (Name == "C") {
		Cast<UCanvasPanelSlot>(CSkill->Slot.Get())->SetSize(FVector2D(60, 60));
	}
	else if (Name == "MR") {
		Cast<UCanvasPanelSlot>(MRSkill->Slot.Get())->SetSize(FVector2D(60, 60));
	}
}

void UMySkillWidget::IconSizeUp(FName Name) {
	if (Name == "Q") {
		Cast<UCanvasPanelSlot>(QSkill->Slot.Get())->SetSize(FVector2D(80, 80));
	}
	else if (Name == "C") {
		Cast<UCanvasPanelSlot>(CSkill->Slot.Get())->SetSize(FVector2D(80, 80));
	}
	else if (Name == "MR") {
		Cast<UCanvasPanelSlot>(MRSkill->Slot.Get())->SetSize(FVector2D(80, 80));
	}
}

void UMySkillWidget::ChangeTextBlockSize(FName _Name, float _NewFontSize, bool UpDown) {
	UTextBlock* YourTextBlock = nullptr;
	if (_Name == "Q") {
		YourTextBlock = QText;
	}
	else if (_Name == "C") {
		YourTextBlock = CText;
	}
	else if (_Name == "MR") {
		YourTextBlock = MRText;
	}
	
	if (YourTextBlock)
	{
		if (UpDown) Cast<UCanvasPanelSlot>(YourTextBlock->Slot.Get())->SetSize(FVector2D(80, 80));
		else  Cast<UCanvasPanelSlot>(YourTextBlock->Slot.Get())->SetSize(FVector2D(60, 60));
		FSlateFontInfo FontInfo = YourTextBlock->Font;  // 현재 폰트 정보를 가져옵니다.
		FontInfo.Size = _NewFontSize;  // 원하는 크기로 폰트 크기를 설정합니다.
		YourTextBlock->SetFont(FontInfo);  // 변경된 폰트 정보를 TextBlock에 설정합니다.
	}
	else
	{
		// TextBlock을 찾지 못했을 경우 에러 메시지를 출력하거나 적절한 예외 처리를 수행하세요.
		UE_LOG(LogTemp, Warning, TEXT("TextBlock을 찾을 수 없습니다."));
	}
}

bool UMySkillWidget::UsingItem(FName _ItemName) {
	for (UWidget* ItemSlot : QuickSlotPanel->GetAllChildren()) {
		UInventoryIconWidget* tmp = Cast<UInventoryIconWidget>(ItemSlot);
		if (tmp->HaveItem->ItemName == _ItemName) {
			tmp->UsingItem();
			return true;
		}
	}
	return false;
}

FName UMySkillWidget::UsingItem(int _Index) {
	UInventoryIconWidget* tmp = Cast<UInventoryIconWidget>(QuickSlotPanel->GetChildAt(_Index));
	if (tmp->HaveItem->IsInItem) {
		FName ReturnItemName = tmp->HaveItem->ItemName;
		tmp->UsingItem();
		return ReturnItemName;
	}
	return EName::None;
}

void UMySkillWidget::SetRoundTimerSecond(int _Second) {
	if (_Second < 10) {
		RoundTimeSecond->SetText(FText::Format(LOCTEXT("0", "0{0}"), _Second));
	}
	else {
		RoundTimeSecond->SetText(FText::AsNumber(_Second));;
	}
}

void UMySkillWidget::SetRoundTimerMinite(int _Minite) {
	if (_Minite < 10) {
		RoundTimeMinite->SetText(FText::Format(LOCTEXT("0","0{0}"), _Minite));
	}
	else {
		RoundTimeMinite->SetText(FText::AsNumber(_Minite));;
	}
}

void UMySkillWidget::QuickSlotItemNumPlus(FName _ItemName) {
	for (UWidget* ItemSlot : QuickSlotPanel->GetAllChildren()) {
		UInventoryIconWidget* tmp = Cast<UInventoryIconWidget>(ItemSlot);
		if (tmp->HaveItem->ItemName == _ItemName) {
			tmp->ItemNumPlus();
			return;
		}
	}
}