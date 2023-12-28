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
	// UI를 움직이기 위한 윗부분 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* InventoryHeader;
	// UI 전체를 담은 캔버스
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* InventoryCanvas;
	// 현재 골드를 표시해 줄 텍스트
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GoldText;
	// 현재 비어있는 칸중 가장 작은 번호
	UPROPERTY()
		int CurrentIndex;
	// 인벤 아이콘을 담은 판넬
	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* InventoryPanel;

	// 캐릭터가 가진 아이템
	UPROPERTY(VisibleAnywhere)
		TMap<FName, class UInventoryIconWidget*> CheckItemList;

	// UI를 움직일 때 필요한 변수들
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
