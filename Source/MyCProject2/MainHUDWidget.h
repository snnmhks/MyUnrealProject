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
	// ��ų ȭ��
	UPROPERTY(meta = (BindWidget))
		class UMySkillWidget* UI_SkillWidget;
	// UI�� ȭ��
	UPROPERTY(meta = (BindWidget))
		class UInventoryWidget* UI_Inventory;

public:
	void UsingItem(FName _ItemName);
};
