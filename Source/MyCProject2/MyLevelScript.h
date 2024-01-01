// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MyLevelScript.generated.h"

/**
 * 
 */

// 레벨 블루프린트를 c++로 가져온것

UCLASS()
class MYCPROJECT2_API AMyLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	int KilledEnemyNum;
	int GameLevel;
	int MaxSpawnEnemyNum;

	// 캐릭터 컨트롤러
	UPROPERTY(VisibleAnywhere)
		class AMyPlayerController* MyCharacterController;

public:
	AMyLevelScript();

	void KilledEnemy();
	void SpawnEnemy();
	void EndShop();

protected:
	virtual void BeginPlay() override;
};
