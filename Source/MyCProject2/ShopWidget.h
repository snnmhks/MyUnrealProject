// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 플레이어
	class AMyCharacter* MyPlayer;

	// 업그레이드 버튼들
	UPROPERTY(meta = (BindWidget))
		class UButton* Damage;
	UPROPERTY(meta = (BindWidget))
		class UButton* AttackSpeed;
	UPROPERTY(meta = (BindWidget))
		class UButton* Defense;
	UPROPERTY(meta = (BindWidget))
		class UButton* Health;
	UPROPERTY(meta = (BindWidget))
		class UButton* Energy;
	UPROPERTY(meta = (BindWidget))
		class UButton* Finish;
	UPROPERTY(meta = (BindWidget))
		class UButton* AutoAttack;
	UPROPERTY(meta = (BindWidget))
		class UButton* MoreGold;
	UPROPERTY(meta = (BindWidget))
		class UButton* MoreEnemy;
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* ExpainWindow;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradeTitle;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ExplainUpgrade;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GoldText;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CrystalText;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradeName;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradeText;
	
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* SOF;

public:
	UFUNCTION()
		void DamageUpgrade();
	UFUNCTION()
		void AttackSpeedUpgrade();
	UFUNCTION()
		void DefenseUpgrade();
	UFUNCTION()
		void HealthUpgrade();
	UFUNCTION()
		void EnergyUpgrade();
	UFUNCTION()
		void EndUpgrade();
	UFUNCTION()
		void SetExplainDamage();
	UFUNCTION()
		void RemoveExplain();
	UFUNCTION()
		void SetExplainAttackSpeed();
	UFUNCTION()
		void SetExplainDefence();
	UFUNCTION()
		void SetExplainHealth();
	UFUNCTION()
		void SetExplainEnergy();
	UFUNCTION()
		void SetExplainAutoAttack();
	UFUNCTION()
		void SetExplainMoreGold();
	UFUNCTION()
		void SetExplainMoreEnemy();

	UFUNCTION()
		void SetGoldText();
	UFUNCTION()
		void SetCrystalText();
	

protected:
	virtual void NativeOnInitialized() override;
};
