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
	// �θ� ����
	UPROPERTY()
		class UMainHUDWidget* ParentWidget;
	// ������ �� �� ���ü��� ���� ǥ���� ������
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ChargeBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ChargeBarText;

	// �κ� �������� ���� �ǳ�
	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* QuickSlotPanel;

	// �� ��ų�� ������
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

	// ���� ��
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HPBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* MPBar;

public:
	// ��Ÿ���� �� Ȯ���ϰ� ���� �� �� �ֵ��� ������ ũ�⸦ ����
	UFUNCTION()
		void IconSizeDown(FName Name);
	UFUNCTION()
		void IconSizeUp(FName Name);
	UFUNCTION()
		void ChangeTextBlockSize(FName _Name, float _NewFontSize, bool UpDown);
	// �����ٸ� Ư�� Ÿ�ֿ̹� �����ְ� �� ���� ������ �Ⱥ��̰� �ϴ� �Լ�
	UFUNCTION()
		void ChargeBarActivate(FName Name);
	UFUNCTION()
		void ChargeBarDisable();
	// Ư�� ��ų�� ����ϸ� ML�������� Ȱ��ȭ�Ͽ� ��ȣ�ۿ� �� �� �ְ� �ϴ� �Լ�
	UFUNCTION()
		void MLActivate();
	UFUNCTION()
		void MLDisable();

	bool UsingItem(FName _ItemName);
	FName UsingItem(int _Index);

protected:
	virtual void NativeOnInitialized() override;
};
