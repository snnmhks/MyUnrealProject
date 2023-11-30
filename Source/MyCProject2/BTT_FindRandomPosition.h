// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_FindRandomPosition.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UBTT_FindRandomPosition : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_FindRandomPosition();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
