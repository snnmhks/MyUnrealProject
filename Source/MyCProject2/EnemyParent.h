// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyParent.generated.h"

UCLASS()
class MYCPROJECT2_API AEnemyParent : public ACharacter
{
	GENERATED_BODY()
private:
	// UI�� �޾ƿ��� ����
	TSubclassOf<class UUserWidget> UI_EnemyClass;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* EWidget;
	// ü�¹� ���ʱ��� �����ֱ�
	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* EWidget2;

private:

public:

	// �÷��̾�
	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* TargetPlayer;

	// ĳ���Ϳ� ������ �ִϸ��̼�
	UPROPERTY(VisibleAnywhere)
		class UEnemyAnimInstance* EnemyAnim;

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

	// ������ ����
	UPROPERTY(VisibleAnywhere)
		class UItemData* ItemData;

public:
	// Sets default values for this pawn's properties
	AEnemyParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �������� ������ ȣ���� �Լ�
	void OnDamaged(float _Damage);

	// �������� �ָ� ȣ���� �Լ�
	float EnemyAttack();

	// �������� �ָ� ȣ���� �Լ�
	void SetItemData();
};
