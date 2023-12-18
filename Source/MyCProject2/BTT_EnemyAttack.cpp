// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_EnemyAttack.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"
#include "EnemyParent.h"

UBTT_EnemyAttack::UBTT_EnemyAttack() {
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTT_EnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AEnemyParent* ControllingPawn = Cast<AEnemyParent>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;
	else {
		FVector TargetVector = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyAIController::KeyTargetPosition);
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), TargetVector);
		ControllingPawn->SetActorRotation(TargetRotation);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AEnemyAIController::KeyMongtageTime, ControllingPawn->EnemyAttack() + 1.0f);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}