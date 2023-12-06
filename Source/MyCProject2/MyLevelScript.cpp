// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLevelScript.h"
#include "Enemy_Bear.h"
#include "EnemyAnimInstance.h"
#include "Math/UnrealMathUtility.h"

AMyLevelScript::AMyLevelScript() {

}

void AMyLevelScript::BeginPlay() {
	Super::BeginPlay();

	// 랜덤 위치에 적을 소환
	AEnemy_Bear* tmp;
	FVector SpawnLocation = FVector::ZeroVector;
	SpawnLocation.X = FMath::RandRange(-1500, 1500);
	SpawnLocation.Y = FMath::RandRange(-1500, 1500);
	tmp = GetWorld()->SpawnActor<AEnemy_Bear>(SpawnLocation, FRotator::ZeroRotator);
}
