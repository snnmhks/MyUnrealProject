// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

UEnemyAnimInstance::UEnemyAnimInstance() {

}

void UEnemyAnimInstance::PlayMongtage(UAnimMontage* _Mongtage) {

	Montage_Play(_Mongtage, 1.0f);
}

void UEnemyAnimInstance::AnimNotify_EndDie() {
	DieCheck.Broadcast();
}