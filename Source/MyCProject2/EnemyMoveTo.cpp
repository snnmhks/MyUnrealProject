// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMoveTo.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Controller.h"
#include "EnemyParent.h"
#include "Tasks/AITask_MoveTo.h"
#include "Kismet/GameplayStatics.h" // GetPlayerController »ç¿ë

UEnemyMoveTo::UEnemyMoveTo() {
	NodeName = TEXT("EnemyMoveTo");
}
//UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()
EBTNodeResult::Type UEnemyMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AEnemyParent* ControllingPawn = Cast<AEnemyParent>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;
	UAITask_MoveTo::AIMoveTo(
		Cast<AAIController>(ControllingPawn->GetController()),
		OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyAIController::KeyTargetPosition),
		nullptr,
		ControllingPawn->AttackRange
	);
	return EBTNodeResult::Succeeded;
}