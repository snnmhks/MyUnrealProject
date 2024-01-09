// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UEnemyMoveTo : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UEnemyMoveTo();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
