// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UEnemyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 적의 체력바, 머리위에 표시되게 하였다.
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HPBar;

public:
	// 체력의 변화가 생기면 이 함수를 호출하여 체력바에 반영되게 한다.
	UFUNCTION()
		void SetHPBarPercent(float Min, float Max);
};
