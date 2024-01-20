// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "ShopWidget.h"


AMyPlayerController::AMyPlayerController() {
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (IsValid(MyPawn)) {
		MyPawn = Cast<AMyCharacter>(GetPawn());
	}
}

void AMyPlayerController::Tick(float DeltaTime) {
	
}