// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLevelScript.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "Enemy_Bear.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h" // GetPlayerController 사용

AMyLevelScript::AMyLevelScript() {
	KilledEnemyNum = 0;
	GameLevel = 1;
	MaxSpawnEnemyNum = 5;
	MyCharacterController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

}

void AMyLevelScript::BeginPlay() {
	Super::BeginPlay();
	//SpawnEnemy();
}

void AMyLevelScript::SpawnEnemy() {
	float Percent = 0.5f;
	int SpawnNum = 0;
	// 랜덤 위치에 적을 소환
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 5; k++) {
			if (FMath::RandRange(0, 1) < Percent) {
				FVector SpawnLocation = FVector::ZeroVector;
				SpawnLocation.X = j * 600 + 300 - 900;
				SpawnLocation.Y = k * 600 + 300 - 1500;
				switch (GameLevel) {
				case 1:
					GetWorld()->SpawnActor<AEnemy_Bear>(SpawnLocation, FRotator(0.0f, 180.0f, 0.0f));
					break;
				case 2:
					GetWorld()->SpawnActor<AEnemy_Bear>(SpawnLocation, FRotator(0.0f, 180.0f, 0.0f));
					break;
				}
				
				Percent = 0.5f;
				SpawnNum++;
				if (SpawnNum == MaxSpawnEnemyNum) break;
			}
			else Percent += 0.1f;
		}
		if (SpawnNum == MaxSpawnEnemyNum) break;
	}
}

void AMyLevelScript::KilledEnemy() {
	KilledEnemyNum++;
	if (KilledEnemyNum == 1) {
		KilledEnemyNum = 0;
		MyCharacterController->OpenShop();
	}
}

void AMyLevelScript::EndShop() {
	MyCharacterController->CloseShop();
	GameLevel++;
	SpawnEnemy();
}