// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindRandomPosition.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTT_FindRandomPosition::UBTT_FindRandomPosition() {
	NodeName = TEXT("FindRandomPosition");
}

EBTNodeResult::Type UBTT_FindRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem) return EBTNodeResult::Failed;

	FVector Orgin = ControllingPawn->GetActorLocation();
	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(Orgin, 500.0f, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::KeyRandomPosition, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}