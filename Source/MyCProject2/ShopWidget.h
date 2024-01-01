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
	// �÷��̾�
	class AMyCharacter* MyPlayer;

	// ���׷��̵� ��ư��
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
	
public:
	UFUNCTION()
		void DamageUpgrade();
	UFUNCTION()
		void EndUpgrade();

protected:
	virtual void NativeOnInitialized() override;
};
