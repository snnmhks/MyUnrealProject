// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartWidget.h"
#include "MyCharacter.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "MyLevelScript.h"
#include "Kismet/GameplayStatics.h"

void UGameStartWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	GamePlay->OnClicked.AddDynamic(this, &UGameStartWidget::StartGame);
	HowToPlay->OnClicked.AddDynamic(this, &UGameStartWidget::ShowHowToPlay);
	Back->OnClicked.AddDynamic(this, &UGameStartWidget::BackToGamePlay);
}

void UGameStartWidget::StartGame() {
	Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn())->RemoveGameStartWindow();
	Cast<AMyLevelScript>(GetWorld()->GetLevelScriptActor())->RoundStart();
}

void UGameStartWidget::ShowHowToPlay() {
	StartWindow->SetVisibility(ESlateVisibility::Collapsed);
	HowToPlayWindow->SetVisibility(ESlateVisibility::Visible);
}

void UGameStartWidget::BackToGamePlay() {
	StartWindow->SetVisibility(ESlateVisibility::Visible);
	HowToPlayWindow->SetVisibility(ESlateVisibility::Collapsed);
}