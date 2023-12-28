// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// UI�� �����̱� ���� ���κ� ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* InventoryHeader;
	// UI ��ü�� ���� ĵ����
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* InventoryCanvas;
	// ���� ��带 ǥ���� �� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GoldText;
	// ���� ����ִ� ĭ�� ���� ���� ��ȣ
	UPROPERTY()
		int CurrentIndex;
	// �κ� �������� ���� �ǳ�
	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* InventoryPanel;

	// ĳ���Ͱ� ���� ������
	UPROPERTY(VisibleAnywhere)
		TMap<FName, class UInventoryIconWidget*> CheckItemList;

	// UI�� ������ �� �ʿ��� ������
	class UCanvasPanelSlot* CanvasSlot;
	FVector2D MousePos;
	FVector2D AfterPos;
	bool IsTimer;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
		void UIMove();
	UFUNCTION()
		void UIMoveStop();

	void SetGoldValue(int _Gold);
	bool AddItemToInventory(class UItemData* _Item);
	bool UsingItem(FName _ItemName);
};
