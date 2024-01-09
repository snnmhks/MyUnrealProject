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
	// Behavior Tree를 담을 변수
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	// Black Board를 담을 변수
	UPROPERTY()
		class UBlackboardData* BBAsset;

public:
	// Black Board에서 가져온 키값을 담을 변수
	static const FName KeyRandomPosition;
	static const FName KeyTargetPosition;
	static const FName KeyMongtageTime;
	static const FName KeyIsInTarget;

public:
	AEnemyAIController();
	// BT를 시작하는 함수와 멈추는 함수
	void RunBT();
	void StopBT();

	//void FindRandomPosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// AI컨트롤러가 빙의 됐을 때 실행되는 함수
	virtual void OnPossess(APawn* InPawn) override;
};
