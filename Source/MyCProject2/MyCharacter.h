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
	// 캐릭터에 필요한 스프링 암과 카메라
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;
	// 캐릭터에 적용할 애니메이션
	UPROPERTY(VisibleAnywhere)
		class UMyAnimInstance* MyAnim;
	// 캐릭터 컨트롤러
	UPROPERTY(VisibleAnywhere)
		class AMyPlayerController* MyController;
	// 여러가지 정보를 가진 데이터 테이블
	UPROPERTY(VisibleAnywhere)
		class UDataTable* SkillDataTable;
	UPROPERTY(VisibleAnywhere)
		class UDataTable* CharacterStateTable;
	// 가끔 대쉬 거리가 짧은 애니메이션이 있으면 선형보간으로 거리를 늘려주기 위한 좌표
	UPROPERTY(VisibleAnywhere)
		FVector TargetPosition;
	// 카메라 관련 변수들
	UPROPERTY(VisibleAnywhere)
		float CameraZoomMin;
	UPROPERTY(VisibleAnywhere)
		float CameraZoomMax;
	UPROPERTY(VisibleAnywhere)
		float CameraRotateScale;
	// 스킬쿨 함수들이 몇초마다 1번씩 돌아가게 할 건지 정하는 변수
	UPROPERTY(VisibleAnywhere)
		float SkillCoolRate;

	// 타이머 핸들러
	FTimerHandle QSkillTimerHandle;
	FTimerHandle QSkillRunTimerHandle;
	FTimerHandle CSkillTimerHandle;
	FTimerHandle MRSkillTimerHandle;
	FTimerHandle MRSkillChargeTimerHandle;
	FTimerHandle RecoverMPTimerHandle;

	// 실시간으로 변하는 쿨타임 관련 변수들
	UPROPERTY(VisibleAnywhere)
		float QSkillCoolValue = 0.f;
	UPROPERTY(VisibleAnywhere)
		float CSkillCoolValue = 0.f;
	UPROPERTY(VisibleAnywhere)
		float MRSkillCoolValue = 0.f;

	// 실시간으로 변하는 변수들
	UPROPERTY(VisibleAnywhere)
		float QSkillRunValue = 0.f;
	UPROPERTY(VisibleAnywhere)
		float ChargeValue;

	// 실시간으로 변하는 캐릭 상태 변수들
	UPROPERTY(VisibleAnywhere)
		float CurrentHP;
	UPROPERTY(VisibleAnywhere)
		float CurrentMP;

public:
	// 데이터 테이블에서 가져온 변수를 저장할 맵
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		TMap<FString, float> SkillData;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		TMap<FString, float> CharacterState;
	// 입력으로 주어지는 움직임 값으로 블랜딩 한다.
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

	// 타격이 가능한 시점인가?
	UPROPERTY(VisibleAnywhere)
		bool IsAttackAble = false;
	// 타격 당한 적
	UPROPERTY(VisibleAnywhere)
		class AEnemyParent* TargetEnemy;
	// 전달할 데미지 값
	UPROPERTY(VisibleAnywhere)
		float DamageValue;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		FString ActionState;

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// 스킬 창에 대한 UI를 받아오는 변수
	TSubclassOf<class UUserWidget> UI_SkillClass;
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UMySkillWidget* UI_Skill;

	// IMC 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputMappingContext* DefaultContext;
	// Move 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_Move;
	// Jump 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_Jump;
	// CameraZoom 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_CameraZoom;
	// Dash 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_Dash;
	// Look 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_Look;
	// ComboAttack 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_ComboAttack;
	// SprintAttack 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_SprintAttack;
	// Dodge 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_DodgeAttack;
	// Heavy Attack 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Input)
		class UInputAction* IA_HeavyAttack;

	// Weapon 변수 설정
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		TSubclassOf<class AMyWeapon> WeaponCalss;
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		class AMyWeapon* Weapon;

protected:
	// 데이터 테이블에서 가져온 변수를 저장하는 함수
	void SetSkillValue();
	void SetCharacterStateValue();
	// 움직임에 대한 IA
	void Move(const FInputActionValue& Value);
	void MoveEnd(const FInputActionValue& Value);
	void DashStart(const FInputActionValue& Value);
	void DashEnd(const FInputActionValue& Value);
	void JumpAction(const FInputActionValue& Value);
	// 시야에 대한 IA
	void Look(const FInputActionValue& Value);
	void CameraZoom(const FInputActionValue& Value);
	// 공격에 대한 IA
	void ComboAttack(const FInputActionValue& Value);
	void SprintAttack(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void HeavyAttack(const FInputActionValue& Value);
	void HeavyEnd(const FInputActionValue& Value);
	// 공격이 끝나면 실행되는 함수 -> 엔진과 상호작용을 해서 UFUNCTION을 붙여줘야함
	UFUNCTION()
		void AttackEnded(UAnimMontage* Montage, bool bInterrupted);

	// 스킬 쿨타임을 돌릴 함수, timer를 통해 실행시킬 함수이다.
	UFUNCTION()
		void QSkillCoolTime();
	UFUNCTION()
		void CSkillCoolTime();
	UFUNCTION()
		void MRSkillCoolTime();

	// Q 스킬 달리기 보여주는 함수, timer를 통해 실행시킬 함수이다.
	UFUNCTION()
		void QSkillRunTime();
	// MR 스킬 차지 상태를 보여주는 함수, timer를 통해 실행시킬 함수이다.
	UFUNCTION()
		void MRSkillChargeTime();

	// HP 조절 함수
	UFUNCTION()
		void DiffHP(float _HP);
	// MP 조절 함수
	UFUNCTION()
		void DiffMP(float _MP);
	// HP 자연 회복 함수
	UFUNCTION()
		void NaturalRecoverHP();
	// MP 자연 회복 함수
	UFUNCTION()
		void NaturalRecoverMP();
};
