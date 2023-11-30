// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

UEnemyAnimInstance::UEnemyAnimInstance() {
	// ��ȯ ��Ÿ�� ����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SPAWN_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Montage/Spawn.Spawn'"));
	if (SPAWN_MONTAGE.Succeeded()) SpawnMontage = SPAWN_MONTAGE.Object;
}

void UEnemyAnimInstance::PlayMongtage(FString Name) {

	if (Name == "Spawn") {
		Montage_Play(SpawnMontage, 1.0f);
	}
}