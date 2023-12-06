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
	// ���� ü�¹�, �Ӹ����� ǥ�õǰ� �Ͽ���.
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HPBar;

public:
	// ü���� ��ȭ�� ����� �� �Լ��� ȣ���Ͽ� ü�¹ٿ� �ݿ��ǰ� �Ѵ�.
	UFUNCTION()
		void SetHPBarPercent(float Min, float Max);
};
