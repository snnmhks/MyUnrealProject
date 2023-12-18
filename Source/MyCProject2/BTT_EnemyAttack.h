// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UBTT_EnemyAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_EnemyAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
