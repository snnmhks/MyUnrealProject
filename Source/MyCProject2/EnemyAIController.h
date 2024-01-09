// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
private:
	// Behavior Tree�� ���� ����
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	// Black Board�� ���� ����
	UPROPERTY()
		class UBlackboardData* BBAsset;

public:
	// Black Board���� ������ Ű���� ���� ����
	static const FName KeyRandomPosition;
	static const FName KeyTargetPosition;
	static const FName KeyMongtageTime;
	static const FName KeyIsInTarget;

public:
	AEnemyAIController();
	// BT�� �����ϴ� �Լ��� ���ߴ� �Լ�
	void RunBT();
	void StopBT();

	//void FindRandomPosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// AI��Ʈ�ѷ��� ���� ���� �� ����Ǵ� �Լ�
	virtual void OnPossess(APawn* InPawn) override;
};
