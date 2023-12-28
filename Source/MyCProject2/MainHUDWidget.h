// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 스킬 화면
	UPROPERTY(meta = (BindWidget))
		class UMySkillWidget* UI_SkillWidget;
	// UI들 화면
	UPROPERTY(meta = (BindWidget))
		class UInventoryWidget* UI_Inventory;

public:
	void UsingItem(FName _ItemName);
};
