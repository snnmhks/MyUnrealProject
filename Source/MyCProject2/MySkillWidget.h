// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MySkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UMySkillWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 부모 위젯
	UPROPERTY()
		class UMainHUDWidget* ParentWidget;
	// 차지를 할 때 가시성을 위해 표시할 차지바
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ChargeBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ChargeBarText;

	// 인벤 아이콘을 담은 판넬
	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* QuickSlotPanel;

	// 각 스킬의 아이콘
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* QSkill;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* QText;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* CSkill;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CText;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* MRSkill;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MRText;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* MLSkill;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MLText;

	// 상태 바
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HPBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* MPBar;

public:
	// 쿨타임일 때 확실하게 구분 할 수 있도록 아이콘 크기를 조절
	UFUNCTION()
		void IconSizeDown(FName Name);
	UFUNCTION()
		void IconSizeUp(FName Name);
	UFUNCTION()
		void ChangeTextBlockSize(FName _Name, float _NewFontSize, bool UpDown);
	// 차지바를 특정 타이밍에 보여주고 할 일이 끝나면 안보이게 하는 함수
	UFUNCTION()
		void ChargeBarActivate(FName Name);
	UFUNCTION()
		void ChargeBarDisable();
	// 특정 스킬을 사용하면 ML아이콘을 활성화하여 상호작용 할 수 있게 하는 함수
	UFUNCTION()
		void MLActivate();
	UFUNCTION()
		void MLDisable();

	bool UsingItem(FName _ItemName);
	FName UsingItem(int _Index);

protected:
	virtual void NativeOnInitialized() override;
};
