// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

// �����忡�� Ű ������
const FName AEnemyAIController::KeyRandomPosition(TEXT("RandomPosition"));
const FName AEnemyAIController::KeyTargetPosition(TEXT("TargetPosition"));
const FName AEnemyAIController::KeyMongtageTime(TEXT("MongtageTime"));

AEnemyAIController::AEnemyAIController() {
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BLACK_BOARD(TEXT("BlackboardData'/Game/AI/BB_Enemy'"));
	if (BLACK_BOARD.Succeeded()) BBAsset = BLACK_BOARD.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BEHAVIOR_TREE(TEXT("BehaviorTree'/Game/AI/BT_Enemy'"));
	if (BLACK_BOARD.Succeeded()) BTAsset = BEHAVIOR_TREE.Object;
}

void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();

}


void AEnemyAIController::RunBT() {
	// ��Ȯ�� �۵� ������ ���� ��
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardComp)) RunBehaviorTree(BTAsset);
}

void AEnemyAIController::StopBT() {
	// ���� ���� �۵��߾� BT�� �����ͼ� ������ �����.
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}

void AEnemyAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	//RunBT();
}
