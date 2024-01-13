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
	// �θ� ����
	UPROPERTY()
		class UMainHUDWidget* ParentWidget;
	// UI�� �����̱� ���� ���κ� ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* InventoryHeader;
	// UI ��ü�� ���� ĵ����
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* InventoryCanvas;
	// ���� ���(����)�� ǥ���� �� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GoldText;
	// ���� �ź��� ũ����Ż�� ǥ���� �� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CrystalText;
	// ���� ����ִ� ĭ�� ���� ���� ��ȣ
	UPROPERTY()
		int CurrentIndex;
	// �κ� �������� ���� �ǳ�
	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* InventoryPanel;

	// ĳ���Ͱ� ���� ������
	TMap<FName, class UInventoryIconWidget*> CheckItemList;

	// UI�� ������ �� �ʿ��� ������
	class UCanvasPanelSlot* CanvasSlot;
	FVector2D MousePos;
	FVector2D AfterPos;
	bool IsTimer;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	// ���콺 ��ư ������ �߻��ϴ� �̺�Ʈ
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UFUNCTION()
		void UIMove();
	UFUNCTION()
		void UIMoveStop();

	void SetGoldValue(int _Gold);
	void SetCrystalValue(int _Gold);
	bool AddItemToInventory(class UItemData* _Item);
	bool UsingItem(FName _ItemName);
};
