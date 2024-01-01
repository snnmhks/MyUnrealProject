// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class AMyCharacter* MyPawn;
	// Shop â�� ���� UI�� �޾ƿ��� ����
	TSubclassOf<class UUserWidget> UI_ShopClass;
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UShopWidget* UI_Shop;

public:
	void OpenShop();
	void CloseShop();

private:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
