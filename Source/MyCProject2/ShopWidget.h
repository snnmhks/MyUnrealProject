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
		class UButton* Defence;
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
	
public:
	UFUNCTION()
		void DamageUpgrade();
	UFUNCTION()
		void EndUpgrade();
	void SetExplainDamage();
	void SetExplainAttackSpeed();
	void SetExplainDefense();
	void SetExplainHealth();
	void SetExplainEnergy();
	void SetExplainAutoAttack();
	void SetExplainMoreGold();
	void SetExplainMoreEnemy();

protected:
	virtual void NativeOnInitialized() override;
};
