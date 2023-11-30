// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "MyCharacter.h"

UMyAnimInstance::UMyAnimInstance() {
	// 점프 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> JUMP_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeWarriors/Character/CompleteCharacters/Mongtage/Jump.Jump'"));
	if (JUMP_MONTAGE.Succeeded()) JumpMontage = JUMP_MONTAGE.Object;

	// 콤보 공격 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> COMBO_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeWarriors/Character/CompleteCharacters/Mongtage/ComboAttack'"));
	if (COMBO_MONTAGE.Succeeded()) ComboMontage = COMBO_MONTAGE.Object;

	// 스프린트 공격 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SPRINT_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeWarriors/Character/CompleteCharacters/Mongtage/SprintAttack.SprintAttack'"));
	if (SPRINT_MONTAGE.Succeeded()) SprintMontage = SPRINT_MONTAGE.Object;

	// 닷지 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DODGE_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeWarriors/Character/CompleteCharacters/Mongtage/Dodge.Dodge'"));
	if (DODGE_MONTAGE.Succeeded()) DodgeMontage = DODGE_MONTAGE.Object;

	// 헤비 어택 몽타주 생성
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HEAVY_MONTAGE(
		TEXT("AnimMontage'/Game/InfinityBladeWarriors/Character/CompleteCharacters/Mongtage/HeavyAttack.HeavyAttack'"));
	if (HEAVY_MONTAGE.Succeeded()) HeavyMontage = HEAVY_MONTAGE.Object;
}

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Player = Cast<AMyCharacter>(TryGetPawnOwner());
}

void UMyAnimInstance::PlayMongtage(FString Name) {
	// 몽타주 재생 함수, 캐릭터 클래스에서는 PlayAnimMongtage 함수를 쓴다.
	if (Name == "Combo") Montage_Play(ComboMontage, 1.0f);
	else if (Name == "Sprint") Montage_Play(SprintMontage, 1.0f);
	else if (Name == "Dodge") Montage_Play(DodgeMontage, 1.0f);
	else if (Name == "Jump") Montage_Play(JumpMontage, 1.0f);
	else if (Name == "Heavy") Montage_Play(HeavyMontage, 1.0f);
}

void UMyAnimInstance::StopMontage(FString Name) {
	// 몽타주 멈추는 함수 처음 숫자는 블랜딩에 대한 수치. 높을 수록 블랜딩이 높아진다.
	if (Name == "Sprint" && Montage_IsPlaying(SprintMontage)) Montage_Stop(0.3f, SprintMontage);
}

// 노티파이 설정
void UMyAnimInstance::AnimNotify_NextCombo() {
	// 델리게이트의 Broadcast는 이 델리게이트에 추가되어 있는 모든걸 실행시킨다.
	OnNextComboCheck.Broadcast();
}

void UMyAnimInstance::AnimNotify_SprintAttackPossible() {
	OnSprintAttackPossible.Broadcast();
}

void UMyAnimInstance::AnimNotify_DodgeToAttackCheck() {
	OnDodgeAttackCheck.Broadcast();
}

void UMyAnimInstance::AnimNotify_NoChargeCheck() {
	OnNoChargeAttackCheck.Broadcast();
}

void UMyAnimInstance::AnimNotify_ChargeCheck() {
	OnChargeAttackCheck.Broadcast();
}

void UMyAnimInstance::AnimNotify_AttackAble() {
	OnAttackAble.Broadcast();
}

void UMyAnimInstance::AnimNotify_AttackDisable() {
	OnAttackDisable.Broadcast();
}

void UMyAnimInstance::AnimNotify_DodgeAttackAble() {
	OnAttackAble.Broadcast();
}

void UMyAnimInstance::AnimNotify_DodgeAttackDisable() {
	OnAttackDisable.Broadcast();
}

// 몽타주 섹션 넘기기
// Montage_JumpToSection(섹션 이름, 적용할 몽타주)
void UMyAnimInstance::NextCombo(int _N, FString Name) {
	switch (_N) {
	case 2:
		if (Name == "Combo") Montage_JumpToSection("Combo2", ComboMontage);
		else if (Name == "Sprint") Montage_JumpToSection("SprintAttack", SprintMontage);
		break;
	case 3:
		Montage_JumpToSection("Combo3", ComboMontage);
		break;
	}
}

void UMyAnimInstance::JumpToDodgeAttack() {
	Montage_JumpToSection("DodgeToAttack", DodgeMontage);
}

void UMyAnimInstance::JumpToLanding() {
	Montage_JumpToSection("Landing", JumpMontage);
}

void UMyAnimInstance::JumpToHeavy1() {
	Montage_JumpToSection("Heavy1", HeavyMontage);
}

void UMyAnimInstance::JumpToHeavy2() {
	Montage_JumpToSection("Heavy2", HeavyMontage);
}