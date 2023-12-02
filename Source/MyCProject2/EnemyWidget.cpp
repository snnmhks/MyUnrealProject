// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWidget.h"
#include "Components/ProgressBar.h" // ProgressBar »ç¿ë

void UEnemyWidget::SetHPBarPercent(float Min, float Max) {
	HPBar->SetPercent(Min / Max);
}