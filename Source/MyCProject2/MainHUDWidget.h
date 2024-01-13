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
	// 가장 앞에 있는 UI
	int MaxZorder;
	TArray<class UUserWidget*> UI_Front;
	// 스킬 화면
	UPROPERTY(meta = (BindWidget))
		class UMySkillWidget* UI_SkillWidget;
	// UI들 화면
	UPROPERTY(meta = (BindWidget))
		class UInventoryWidget* UI_Inventory;
	// 상점 창 화면
	UPROPERTY(meta = (BindWidget))
		class UShopWidget* UI_Shop;

public:
	void UsingItemQuickSlot(FName _ItemName);
	void UsingItemInventory(FName _ItemName);
	bool CloseFrontUI();
	void AddToFrontUI(class UUserWidget* _AddWidget);
	void RemoveByFrontUI(class UUserWidget* _AddWidget);

protected:
	virtual void NativeOnInitialized() override;
};
