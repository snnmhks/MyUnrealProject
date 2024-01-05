// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

UEnemyAnimInstance::UEnemyAnimInstance() {

}

void UEnemyAnimInstance::NativeBeginPlay() {
	Super::NativeBeginPlay();

}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* EnemyOwner = TryGetPawnOwner();
	if (IsValid(EnemyOwner)) {
		EnemyVelocity = EnemyOwner->GetVelocity().Size();
	}
}

float UEnemyAnimInstance::PlayMongtage(UAnimMontage* _Mongtage) {
	CurrentMongtage = _Mongtage;
	return Montage_Play(_Mongtage, 1.0f);
}

void UEnemyAnimInstance::AnimNotify_EndDie() {
	DieCheck.Broadcast();
}

void UEnemyAnimInstance::AnimNotify_SpawnFinish() {
	SpawnCheck.Broadcast();
}

void UEnemyAnimInstance::AnimNotify_Attacking() {
	AttackCheck.Broadcast();
}

void UEnemyAnimInstance::StopCurrentMongtage() {
	if (CurrentMongtage) Montage_Stop(0.0f, CurrentMongtage);
}