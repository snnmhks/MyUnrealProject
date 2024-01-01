// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "ShopWidget.h"


AMyPlayerController::AMyPlayerController() {
	PrimaryActorTick.bCanEverTick = true;

	// UI »ý¼º
	static ConstructorHelpers::FClassFinder<UShopWidget> UI_SHOP(
		TEXT("WidgetBlueprint'/Game/UI/UI_Shop'"));
	if (UI_SHOP.Succeeded()) {
		UI_ShopClass = UI_SHOP.Class;
	}
}

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (IsValid(MyPawn)) {
		MyPawn = Cast<AMyCharacter>(GetPawn());
	}
	//if (IsValid(UI_ShopClass)) {
	//	UI_Shop = Cast<UShopWidget>(CreateWidget(GetWorld(), UI_ShopClass));
	//	UI_Shop->AddToViewport();
	//}
}

void AMyPlayerController::Tick(float DeltaTime) {

}

void AMyPlayerController::OpenShop() {
	//UI_Shop->SetVisibility(ESlateVisibility::Visible);
	//SetShowMouseCursor(true);
	//SetInputMode(FInputModeUIOnly());
	//SetPause(true);
}

void AMyPlayerController::CloseShop() {
	//UI_Shop->SetVisibility(ESlateVisibility::Collapsed);
	//SetPause(false);
	//SetShowMouseCursor(false);
	//SetInputMode(FInputModeGameOnly());
}