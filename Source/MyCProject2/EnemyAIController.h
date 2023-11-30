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
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;

public:
	static const FName KeyRandomPosition;
	static const FName KeyTargetPosition;

public:
	AEnemyAIController();

	void RunBT();
	void StopBT();

	//void FindRandomPosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
};
