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
	// �״� ��� ���ΰ�
	UPROPERTY(VisibleAnywhere)
		bool IsDying;

private:

public:

	// ĳ���Ϳ� ������ �ִϸ��̼�
	UPROPERTY(VisibleAnywhere)
		class UEnemyAnimInstance* EnemyAnim;

	// ���� ���� ����
	UPROPERTY(VisibleAnywhere)
		float EnemyMaxHP;
	UPROPERTY(VisibleAnywhere)
		float EnemyCurrentHP;

	// �״� ��Ÿ��
	UPROPERTY(VisibleAnywhere)
		class UAnimMontage* DieMongtage;

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

	void OnDamaged(float _Damage);
};
