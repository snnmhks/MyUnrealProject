// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyCharacter.generated.h"

UCLASS()
class MYCPROJECT2_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	// ĳ���Ϳ� �ʿ��� ������ �ϰ� ī�޶�
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;
	// ĳ���Ϳ� ������ �ִϸ��̼�
	UPROPERTY(VisibleAnywhere)
		class UMyAnimInstance* MyAnim;
	// ĳ���� ��Ʈ�ѷ�
	UPROPERTY(VisibleAnywhere)
		class AMyPlayerController* MyController;
	// �������� ������ ���� ������ ���̺�
	UPROPERTY(VisibleAnywhere)
		class UDataTable* SkillDataTable;
	UPROPERTY(VisibleAnywhere)
		class UDataTable* CharacterStateTable;
	// ���� �뽬 �Ÿ��� ª�� �ִϸ��̼��� ������ ������������ �Ÿ��� �÷��ֱ� ���� ��ǥ
	UPROPERTY(VisibleAnywhere)
		FVector TargetPosition;
	// ī�޶� ���� ������
	UPROPERTY(VisibleAnywhere)
		float CameraZoomMin;
	UPROPERTY(VisibleAnywhere)
		float CameraZoomMax;
	UPROPERTY(VisibleAnywhere)
		float CameraRotateScale;
	// ��ų�� �Լ����� ���ʸ��� 1���� ���ư��� �� ���� ���ϴ� ����
	// ���ڰ� �������� �� ���� ȣ���Ͽ� �ڿ������� ��Ÿ���� �����ϳ� �ʹ� ���� ȣ���ϸ� ������ ��������.
	UPROPERTY(VisibleAnywhere)
		float SkillCoolRate;

	// Ÿ�̸� �ڵ鷯
	FTimerHandle QSkillTimerHandle;
	FTimerHandle QSkillRunTimerHandle;
	FTimerHandle CSkillTimerHandle;
	FTimerHandle MRSkillTimerHandle;
	FTimerHandle MRSkillChargeTimerHandle;
	FTimerHandle RecoverMPTimerHandle;
	FTimerHandle DieTimerHandle;

	// �ǽð����� ���ϴ� ��Ÿ�� ���� ������
	UPROPERTY(VisibleAnywhere)
		float QSkillCoolValue = 0.f;
	UPROPERTY(VisibleAnywhere)
		float CSkillCoolValue = 0.f;
	UPROPERTY(VisibleAnywhere)
		float MRSkillCoolValue = 0.f;

	// �ǽð����� ���ϴ� ������
	UPROPERTY(VisibleAnywhere)
		float QSkillRunValue = 0.f;
	UPROPERTY(VisibleAnywhere)
		float ChargeValue;

	// �ǽð����� ���ϴ� ĳ�� ���� ������
	UPROPERTY(VisibleAnywhere)
		float CurrentHP;
	UPROPERTY(VisibleAnywhere)
		float CurrentMP;

public:
	// ������ ���̺��� ������ ������ ������ ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		TMap<FString, float> SkillData;
	// �ڽ��� ���´� (����, ����, ����)
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		TMap<FString, FVector> SkillArea;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		TMap<FString, float> CharacterState;
	// �Է����� �־����� ������ ������ ���� �Ѵ�.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		FVector2D MoveValue;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		int DashValue;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		int ComboNum;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		bool IsCombo;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		int IsCharge;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		bool IsRecoverMP;

	// Ÿ���� ������ �����ΰ�?
	UPROPERTY(VisibleAnywhere)
		bool IsAttackAble = false;
	// Ÿ�� ���� ��
	UPROPERTY(VisibleAnywhere)
		class AEnemyParent* TargetEnemy;
	// ������ ������ ��
	UPROPERTY(VisibleAnywhere)
		float DamageValue;
	// Sweep Trace �� ��
	UPROPERTY(VisibleAnywhere)
		float AttackRange;
	UPROPERTY(VisibleAnywhere)
		FVector AttackBox; // (����, ����, �Ÿ�) ĳ���� �ٶ󺸰� �ִ� ���� ����
	// �� ��Ʈ�� ������ ���� ĳ������ ���¸� ��Ÿ���� ���� ���°� ���ļ� �߻����� �ʵ��� �Ѵ�.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		FString ActionState;

	// ���׷��̵� ������
	UPROPERTY(VisibleAnywhere)
		float AttackSpeed;
	UPROPERTY(VisibleAnywhere)
		float CoolTimeDown;
	UPROPERTY(VisibleAnywhere)
		float BaseDamage;
	UPROPERTY(VisibleAnywhere)
		float BaseGuard;
	UPROPERTY(VisibleAnywhere)
		float UserGold;

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// HP ���� �Լ�
	UFUNCTION()
		void DiffHP(float _HP);
	// MP ���� �Լ�
	UFUNCTION()
		void DiffMP(float _MP);
	// ��� ���� �Լ�
	UFUNCTION()
		void GoldDiff(int _Gold);
	// ������ �߰� �Լ�
	UFUNCTION()
		bool GetItem(class UItemData* _Item);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// ��ų â�� ���� UI�� �޾ƿ��� ����
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UMySkillWidget* UI_Skill;
	// �κ��丮 â�� ���� UI�� �޾ƿ��� ����
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UInventoryWidget* UI_Inventory;
	// ���� HUD â�� ���� UI�� �޾ƿ��� ����
	TSubclassOf<class UUserWidget> UI_MainHUDClass;
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UMainHUDWidget* UI_MainHUD;

	// IMC ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputMappingContext* DefaultContext;
	// Move ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_Move;
	// Jump ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_Jump;
	// CameraZoom ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_CameraZoom;
	// Dash ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_Dash;
	// Look ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_Look;
	// ComboAttack ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_ComboAttack;
	// SprintAttack ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_SprintAttack;
	// Dodge ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_DodgeAttack;
	// Heavy Attack ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_HeavyAttack;
	// Inventory ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_Inventory;
	// Quick Slot ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_Quick;
	// Close UI ���� ����
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_CloseUI;

	// Weapon ���� ����
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		TSubclassOf<class AMyWeapon> WeaponCalss;
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		class AMyWeapon* Weapon;

protected:
	// ������ ���̺��� ������ ������ �����ϴ� �Լ�
	void SetSkillValue();
	void SetCharacterStateValue();
	// �����ӿ� ���� IA
	void Move(const FInputActionValue& Value);
	void MoveEnd(const FInputActionValue& Value);
	void DashStart(const FInputActionValue& Value);
	void DashEnd(const FInputActionValue& Value);
	void JumpAction(const FInputActionValue& Value);
	// �þ߿� ���� IA
	void Look(const FInputActionValue& Value);
	void CameraZoom(const FInputActionValue& Value);
	// ���ݿ� ���� IA
	void ComboAttack(const FInputActionValue& Value);
	void SprintAttack(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void HeavyAttack(const FInputActionValue& Value);
	void HeavyEnd(const FInputActionValue& Value);
	// �κ��丮�� ���� IA
	void InventoryOnOff(const FInputActionValue& Value);
	// �� ���Կ� ���� IA
	void UsingQuickSlot(const FInputActionValue& Value);
	// UI�ݴ� Ű�� ���� IA
	void CloseUI(const FInputActionValue& Value);
	// �κ��丮 Ŭ�� Ű�� ���� IA
	void InventoryClick(const FInputActionValue& Value);
	// ������ ������ ����Ǵ� �Լ� -> ������ ��ȣ�ۿ��� �ؼ� UFUNCTION�� �ٿ������
	UFUNCTION()
		void AttackEnded(UAnimMontage* Montage, bool bInterrupted);

	// ��ų ��Ÿ���� ���� �Լ�, timer�� ���� �����ų �Լ��̴�.
	UFUNCTION()
		void QSkillCoolTime();
	UFUNCTION()
		void CSkillCoolTime();
	UFUNCTION()
		void MRSkillCoolTime();

	// Q ��ų �޸��� �����ִ� �Լ�, timer�� ���� �����ų �Լ��̴�.
	UFUNCTION()
		void QSkillRunTime();
	// MR ��ų ���� ���¸� �����ִ� �Լ�, timer�� ���� �����ų �Լ��̴�.
	UFUNCTION()
		void MRSkillChargeTime();

	// HP �ڿ� ȸ�� �Լ�. timer�� ����Ͽ� HP �����Լ��� ���������� ȣ���Ѵ�.
	UFUNCTION()
		void NaturalRecoverHP();
	// MP �ڿ� ȸ�� �Լ�. timer�� ����Ͽ� MP �����Լ��� ���������� ȣ���Ѵ�.
	UFUNCTION()
		void NaturalRecoverMP();
	// ������ n�ʵ� ȣ���� �Լ�
	UFUNCTION()
		void Diying();

};
