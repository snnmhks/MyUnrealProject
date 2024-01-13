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
	// ���� �տ� �ִ� UI
	int MaxZorder;
	TArray<class UUserWidget*> UI_Front;
	// ��ų ȭ��
	UPROPERTY(meta = (BindWidget))
		class UMySkillWidget* UI_SkillWidget;
	// UI�� ȭ��
	UPROPERTY(meta = (BindWidget))
		class UInventoryWidget* UI_Inventory;
	// ���� â ȭ��
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
