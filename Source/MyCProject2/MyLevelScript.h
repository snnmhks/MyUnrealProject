// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MyLevelScript.generated.h"

/**
 * 
 */

// ���� �������Ʈ�� c++�� �����°�

UCLASS()
class MYCPROJECT2_API AMyLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	int KilledEnemyNum;
	int GameLevel;
	int MaxSpawnEnemyNum;
	int SpawnNum;

	// ĳ����
	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* MyCharacter;

	// Ÿ�̸� �ڵ鷯
	FTimerHandle SpawnTimerHandle;

public:
	AMyLevelScript();

	void KilledEnemy();
	void SpawnEnemy();
	void EndShop();

protected:
	virtual void BeginPlay() override;
};
