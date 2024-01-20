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
	int GameLevel;			// 게임 라운드 단계
	int MaxSpawnNumInLevel;	// 한번에 소환될 수 있는 몬스터 수
	int KilledEnemyNum;		// 잡은 몬스터 수
	int RoundTimeSecond;	// 라운드 남은 초
	int RoundTimeMinite;	// 라운드 남은 분

	TArray<class AEnemyParent*> EnemyList;
	// 캐릭터
	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* MyCharacter;

	// 타이머 핸들러
	FTimerHandle RoundTimerHandle;	// 라운드의 제한시간 확인

public:
	AMyLevelScript();

	// 적이 죽으면 호출될 함수
	void KilledEnemy();	
	// 적 소환 함수
	void SpawnEnemy();
	// 업그레이드 단계 끝내기
	void EndShop();
	// 라운드 시작
	void RoundStart();
	// 라운드 끝
	void RoundEnd();
	// 라운드 시간
	void SetRoundTimer();


protected:
	virtual void BeginPlay() override;
};
