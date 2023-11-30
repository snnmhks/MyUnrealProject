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
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ChargeBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ChargeBarText;

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

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HPBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* MPBar;

public:
	UFUNCTION()
		void IconSizeDown(FString Name);
	UFUNCTION()
		void IconSizeUp(FString Name);
	UFUNCTION()
		void ChargeBarActivate(FString Name);
	UFUNCTION()
		void ChargeBarDisable();
	UFUNCTION()
		void MLActivate();
	UFUNCTION()
		void MLDisable();
};
