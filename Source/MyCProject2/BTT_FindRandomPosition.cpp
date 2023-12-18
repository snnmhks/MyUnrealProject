// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindRandomPosition.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/Controller.h"
#include "EnemyParent.h"

UBTT_FindRandomPosition::UBTT_FindRandomPosition() {
	NodeName = TEXT("FindPlayerPosition");
}

EBTNodeResult::Type UBTT_FindRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem) return EBTNodeResult::Failed;

	APawn* TargetPlayer = Cast<AEnemyParent>(ControllingPawn)->TargetPlayer;
	if (TargetPlayer) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::KeyTargetPosition, TargetPlayer->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}

	/*
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (NavSystem) return EBTNodeResult::Failed;

	FVector Orgin = ControllingPawn->GetActorLocation();
	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(Orgin, 500.0f, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::KeyRandomPosition, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}
	*/

	return EBTNodeResult::Failed;
}