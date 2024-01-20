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
	int GameLevel;			// ���� ���� �ܰ�
	int MaxSpawnNumInLevel;	// �ѹ��� ��ȯ�� �� �ִ� ���� ��
	int KilledEnemyNum;		// ���� ���� ��
	int RoundTimeSecond;	// ���� ���� ��
	int RoundTimeMinite;	// ���� ���� ��

	TArray<class AEnemyParent*> EnemyList;
	// ĳ����
	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* MyCharacter;

	// Ÿ�̸� �ڵ鷯
	FTimerHandle RoundTimerHandle;	// ������ ���ѽð� Ȯ��

public:
	AMyLevelScript();

	// ���� ������ ȣ��� �Լ�
	void KilledEnemy();	
	// �� ��ȯ �Լ�
	void SpawnEnemy();
	// ���׷��̵� �ܰ� ������
	void EndShop();
	// ���� ����
	void RoundStart();
	// ���� ��
	void RoundEnd();
	// ���� �ð�
	void SetRoundTimer();


protected:
	virtual void BeginPlay() override;
};
