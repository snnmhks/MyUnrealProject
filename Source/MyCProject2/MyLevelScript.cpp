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
	GameLevel = 1;
	MaxSpawnNumInLevel = 5;
}

void AMyLevelScript::BeginPlay() {
	Super::BeginPlay();
	MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

void AMyLevelScript::SpawnEnemy() {
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
					EnemyList.Add(GetWorld()->SpawnActor<AEnemy_Bear>(SpawnLocation, FRotator(0.0f, 180.0f, 0.0f)));
					break;
				case 2:
					EnemyList.Add(GetWorld()->SpawnActor<AEnemy_Spider>(SpawnLocation, FRotator(0.0f, 180.0f, 0.0f)));
					break;
				case 3:
					EnemyList.Add(GetWorld()->SpawnActor<AEnemy_Grunt>(SpawnLocation, FRotator(0.0f, 180.0f, 0.0f)));
					break;
				}
				Percent = 0.5f;
				SpawnEnemyNum++;
				if (SpawnEnemyNum == MaxSpawnNumInLevel) break;
			}
			else Percent += 0.1f;
		}
		if (SpawnEnemyNum == MaxSpawnNumInLevel) break;
	}
}

void AMyLevelScript::KilledEnemy() {
	KilledEnemyNum++;
	if (KilledEnemyNum >= MaxSpawnNumInLevel) {
		KilledEnemyNum = 0;
		SpawnEnemy();
	}
}

void AMyLevelScript::RoundStart() {
	SpawnEnemy();
	RoundTimeSecond = 0;
	RoundTimeMinite = 3;
	GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &AMyLevelScript::SetRoundTimer, 1, true, 0);
}

void AMyLevelScript::RoundEnd() {
	MyCharacter->ShopOnOff(true);
	GetWorldTimerManager().ClearTimer(RoundTimerHandle);
	for (AEnemyParent* EP : EnemyList) {
		EP->Destroy();
	}
}

void AMyLevelScript::SetRoundTimer() {
	if (RoundTimeSecond == 0) {
		if (RoundTimeMinite == 0) {
			RoundEnd();
			return;
		}
		else {
			RoundTimeSecond = 60;
			RoundTimeMinite--;
		}
	}
	RoundTimeSecond--;
	MyCharacter->SetRoundTime(RoundTimeMinite, RoundTimeSecond);
}

void AMyLevelScript::EndShop() {
	MyCharacter->ShopOnOff(false);
	GameLevel++;
	RoundStart();
}