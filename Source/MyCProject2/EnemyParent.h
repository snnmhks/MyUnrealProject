// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyParent.generated.h"

UENUM()
enum class EAttackState {
	LD_Attack = 0,
	Basic_Attack
};

UCLASS()
class MYCPROJECT2_API AEnemyParent : public ACharacter
{
	GENERATED_BODY()
private:
	// UI�� �޾ƿ��� ����
	TSubclassOf<class UUserWidget> UI_EnemyClass;

private:

public:

	FTimerHandle DieTimerHandle;

	float AttackSpeed;
	float AttackRange;
	float AttackRadius;
	float LDAttackRange;
	float LDAttackRadius;

	float AddGiveGold;

	EAttackState AS;

	// �÷��̾�
	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* TargetPlayer;

	// ĳ���Ϳ� ������ �ִϸ��̼�
	UPROPERTY(VisibleAnywhere)
		class UEnemyAnimInstance* EnemyAnim;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* EWidget;

	// ���� ���� ����
	UPROPERTY(VisibleAnywhere)
		float EnemyMaxHP;
	UPROPERTY(VisibleAnywhere)
		float EnemyCurrentHP;
	UPROPERTY(VisibleAnywhere)
		float EnemyDamage;
	UPROPERTY(VisibleAnywhere)
		int EnemyGold;

	// �״� ��� ���ΰ�
	UPROPERTY(VisibleAnywhere)
		bool IsDying;

	// �״� ��Ÿ��
	UPROPERTY(VisibleAnywhere)
		class UAnimMontage* DieMongtage;
	// ��ȯ ��Ÿ��
	UPROPERTY(VisibleAnywhere)
		class UAnimMontage* SpawnMontage;
	// ���� ��Ÿ��
	UPROPERTY(VisibleAnywhere)
		class UAnimMontage* AttackMontage1;
	UPROPERTY(VisibleAnywhere)
		class UAnimMontage* LDAttackMontage1;

	// ������ ����
	UPROPERTY(VisibleAnywhere)
		class UItemData* ItemData;

public:
	// Sets default values for this pawn's properties
	AEnemyParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// ����Ʈ ȣ�� �Լ�
	virtual void PlayEffect();
	virtual void PlayHittedEffect(FVector SpawnLocation);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �������� ������ ȣ���� �Լ�
	void OnDamaged(float _Damage);

	// �������� �ָ� ȣ���� �Լ�
	float EnemyAttack();
	float EnemyLDAttack();

	// ������ �� �� ȣ���� �Լ�
	bool SetItemData();
	void GiveGold();
	void GiveCrystal();

	// ������ ȣ���� �Լ�
	void Diying();
};
