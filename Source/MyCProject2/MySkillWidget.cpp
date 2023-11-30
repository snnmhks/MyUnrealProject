// Fill out your copyright notice in the Description page of Project Settings.

#include "MySkillWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Fonts/SlateFontInfo.h"

#define LOCTEXT_NAMESPACE "MyNameSpace"

void UMySkillWidget::ChargeBarActivate(FString Name) {
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

void UMySkillWidget::IconSizeDown(FString Name) {
	if (Name == "Q") {
		Cast<UCanvasPanelSlot>(QSkill->Slot.Get())->SetSize(FVector2D(60, 60));
		//QText->SetFont(FSlateFontInfo());
	}
	else if (Name == "C") {
		Cast<UCanvasPanelSlot>(CSkill->Slot.Get())->SetSize(FVector2D(60, 60));
		//CText->Font.Size = 45;
	}
	else if (Name == "MR") {
		Cast<UCanvasPanelSlot>(MRSkill->Slot.Get())->SetSize(FVector2D(60, 60));
		//MRText->Font.Size = 26;
	}
}

void UMySkillWidget::IconSizeUp(FString Name) {
	if (Name == "Q") {
		Cast<UCanvasPanelSlot>(QSkill->Slot.Get())->SetSize(FVector2D(80, 80));
		//QText->Font.Size = 60;
	}
	else if (Name == "C") {
		Cast<UCanvasPanelSlot>(CSkill->Slot.Get())->SetSize(FVector2D(80, 80));
		//CText->Font.Size = 60;
	}
	else if (Name == "MR") {
		Cast<UCanvasPanelSlot>(MRSkill->Slot.Get())->SetSize(FVector2D(80, 80));
		//MRText->Font.Size = 35;
	}
}