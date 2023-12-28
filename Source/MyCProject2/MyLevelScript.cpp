// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLevelScript.h"
#include "Enemy_Bear.h"
#include "EnemyAnimInstance.h"
#include "Math/UnrealMathUtility.h"

AMyLevelScript::AMyLevelScript() {

}

void AMyLevelScript::BeginPlay() {
	Super::BeginPlay();
	return;
	float Percent = 0.5f;
	int SpawnNum = 0;
	// 랜덤 위치에 적을 소환
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 5; k++) {
			if (FMath::RandRange(0, 1) < Percent) {
				AEnemy_Bear* tmp;
				FVector SpawnLocation = FVector::ZeroVector;
				SpawnLocation.X = j * 600 + 300 - 900;
				SpawnLocation.Y = k * 600 + 300 - 1500;
				tmp = GetWorld()->SpawnActor<AEnemy_Bear>(SpawnLocation, FRotator(0.0f, 180.0f, 0.0f));
				Percent = 0.5f;
				SpawnNum++;
				if (SpawnNum == 10) break;
			}
			else Percent += 0.1f;
		}
		if (SpawnNum == 10) break;
	}

}
