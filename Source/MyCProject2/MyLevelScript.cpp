// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLevelScript.h"
#include "MyCharacter.h"
#include "MyCharacter.h"
#include "Enemy_Bear.h"
#include "Enemy_Spider.h"
#include "Enemy_Grunt.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h" // GetPlayerController 사용

AMyLevelScript::AMyLevelScript() {
	KilledEnemyNum = 0;
	GameLevel = 1;
	MaxSpawnEnemyNum = 20;
	SpawnNum = 0;
}

void AMyLevelScript::BeginPlay() {
	Super::BeginPlay();
	//GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AMyLevelScript::SpawnEnemy, 10, true, 0);
	MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

void AMyLevelScript::SpawnEnemy() {
	SpawnNum++;
	float Percent = 0.5f;
	int SpawnEnemyNum = 0;
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
					GetWorld()->SpawnActor<AEnemy_Spider>(SpawnLocation, FRotator(0.0f, 180.0f, 0.0f));
					break;
				case 3:
					GetWorld()->SpawnActor<AEnemy_Grunt>(SpawnLocation, FRotator(0.0f, 180.0f, 0.0f));
					break;
				}
				
				Percent = 0.5f;
				SpawnEnemyNum++;
				if (SpawnEnemyNum == 5) break;
			}
			else Percent += 0.1f;
		}
		if (SpawnEnemyNum == 5) break;
	}
	if (SpawnNum == 4) {
		SpawnNum = 0;
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void AMyLevelScript::KilledEnemy() {
	KilledEnemyNum++;
	if (KilledEnemyNum >= MaxSpawnEnemyNum) {
		KilledEnemyNum = 0;
		MyCharacter->ShopOnOff(true);
	}
}

void AMyLevelScript::EndShop() {
	MyCharacter->ShopOnOff(false);
	GameLevel++;
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AMyLevelScript::SpawnEnemy, 10, true, 0);
}