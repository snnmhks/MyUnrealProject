// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "MyAnimInstance.h"
#include "MyWeapon.h"
#include "MyPlayerController.h"
#include "MySkillWidget.h"
#include "SkillDataStruct.h"
#include "CharacterStateStruct.h"
#include "GameFramework/SpringArmComponent.h"//SpringArm ����ϱ� ����
#include "Camera/CameraComponent.h"//Camera ����ϱ� ����
#include "Components/CapsuleComponent.h"//CapsuleComponent ����ϱ� ����
#include "EnhancedInputComponent.h" // �� 3�ٱ��� Enhanced Input�� ����ϱ� ���� ���
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h" // CharacterMovement�� ����ϱ� ����
#include "Engine/SkeletalMeshSocket.h" // ��Ĺ�� ����ϱ� ����
#include "Math/UnrealMathUtility.h" // �𸮾󿡼� �����ϴ� ���� �Լ���
#include "Engine/DataTable.h" // ������ ���̺� ���
#include "Components/ProgressBar.h" // ProgressBar ���
#include "EnemyParent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���� ����/////////////////////

	// ���� ����
	// GetCharacterMovement()->JumpZVelocity = 500.0f;	// ���� ����.
	// JumpMaxCount = 2;								// �ѹ��� ���� ������ Ƚ��. 1�� �⺻ ��.
	// JumpMaxHoldTime = 3.0f;							// ������ �����ϴ� �ð�
	// 
	// ������ ����
	DashValue = 1;										// 1�̸� �ɾ�� 2�� �ڴ�									
	GetCharacterMovement()->MaxWalkSpeed = 300;			// �ʱ� ���� �ӵ�
	//
	// ��Ʈ�ѷ�
	// 
	// ���� ����
	ActionState = "Idle";								// ���� ĳ������ ���¸� ǥ��
														// ���� ĳ������ ���¸� ���� ���� �ൿ�� ���� �������� �ʵ��� �Ͽ���.
	ComboNum = 1;										// �޺� ������ �� ���° �޺����� ��Ÿ����.
	IsCombo = 0;										// �޺� ���� Ű�� �����ؼ� ���� �޺� ������ �� �� �Ǵ��Ѵ�.
	ChargeValue = 0;									// ��� ������ ���� ������ ǥ���ϴ� ��ġ
	IsCharge = 0;										// ������ ������ ��ŭ �ƴ����� �Ǵ��Ͽ� ���� ��� ������ �Ǵ��Ѵ�.
	SkillCoolRate = 0.01f;								// ��ų ��Ÿ�� ������ �Լ��� ���ʸ��� �ѹ��� ������ �� ���ΰ�
	DamageValue = 0.0f;
														// 
	// ī�޶� ����
	CameraZoomMin = 150.f;								// �پ��ٿ��� ���� ���ξƿ��� �ּ� �� �ִ� ����
	CameraZoomMax = 800.f;
	CameraRotateScale = 1.f;							// Ư�� ��ų �߿��� ī�޶� ȸ�� �ӵ��� �����ϱ� ���� ����
	//
	// ���׷��̵� ����
	AttackSpeed = 1.0f;
	CoolTimeDown = 1.0f;
	BaseDamage = 0.0f;
	BaseGuard = 0.0f;
	////////////////////////////////

	// Component ����
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Component ���̱�
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	// Component initail transtrom ����
	SpringArm->TargetArmLength = 500.f;
	SpringArm->TargetOffset.Z = 100.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	// ī�޶� �����̱� ���� �۾�
	SpringArm->bUsePawnControlRotation = true; // �̰� ����� Look�Լ��� AddController~Input�� ������.

	// ĳ���� �Ž� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(
		TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Golden.SK_CharM_Golden'"));
	if (CharacterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
		//GetArrowComponent()->SetupAttachment(GetMesh());
	}

	// �浹 ����
	GetMesh()->SetCollisionProfileName("PlayerMesh");
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetNotifyRigidBodyCollision(true);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(false);

	// ��ų ������ ���̺� ����
	static ConstructorHelpers::FObjectFinder<UDataTable> SKILL_DATA_TABLE(
		TEXT("/Script/Engine.DataTable'/Game/DataTable/SkillDataTable'"));
	if (SKILL_DATA_TABLE.Succeeded()) {
		SkillDataTable = SKILL_DATA_TABLE.Object;
	}

	// ĳ���� ���� ���� ������ ���̺� ����
	static ConstructorHelpers::FObjectFinder<UDataTable> CHARACTER_STATE_TABLE(
		TEXT("/Script/Engine.DataTable'/Game/DataTable/CharacterStateTable'"));
	if (CHARACTER_STATE_TABLE.Succeeded()) {
		CharacterStateTable = CHARACTER_STATE_TABLE.Object;
	}

	// UI ����
	static ConstructorHelpers::FClassFinder<UMySkillWidget> UI_SKILLWIDGET(
		TEXT("WidgetBlueprint'/Game/UI/UI_SkillWidget'"));
	if (UI_SKILLWIDGET.Succeeded()) {
		UI_SkillClass = UI_SKILLWIDGET.Class;
	}
	
	// ���� ����
	static ConstructorHelpers::FClassFinder<AMyWeapon> MY_WEAPON(
		TEXT("Class'/Script/MyCProject2.MyWeapon'"));
	if (MY_WEAPON.Succeeded()) WeaponCalss = MY_WEAPON.Class;

	// �ִϸ��̼� ����
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> MYANIM(
		TEXT("AnimBlueprint'/Game/InfinityBladeWarriors/Character/CompleteCharacters/ABP/ABP_MyCharacter'"));
	if (MYANIM.Succeeded()) GetMesh()->SetAnimInstanceClass(MYANIM.Class);

	// IMC ����
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>IMC_MYCHARACTER
	(TEXT("InputMappingContext'/Game/Input/IMC_MyCharacter.IMC_MyCharacter'"));
	if (IMC_MYCHARACTER.Succeeded()) DefaultContext = IMC_MYCHARACTER.Object;

	// IA Move ����
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_MOVE
	(TEXT("InputAction'/Game/Input/IA/IA_Move.IA_Move'"));
	if (IA_MOVE.Succeeded()) IA_Move = IA_MOVE.Object;

	// IA Jump ����
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_JUMP
	(TEXT("InputAction'/Game/Input/IA/IA_Jump.IA_Jump'"));
	if (IA_JUMP.Succeeded()) IA_Jump = IA_JUMP.Object;

	// IA CameraZoom ����
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_CAMERAZOOM
	(TEXT("InputAction'/Game/Input/IA/IA_CameraZoom.IA_CameraZoom'"));
	if (IA_CAMERAZOOM.Succeeded()) IA_CameraZoom = IA_CAMERAZOOM.Object;

	// IA Dash ����
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_DASH
	(TEXT("InputAction'/Game/Input/IA/IA_Dash.IA_Dash'"));
	if (IA_DASH.Succeeded()) IA_Dash = IA_DASH.Object;

	// IA Look ����
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_LOOK
	(TEXT("InputAction'/Game/Input/IA/IA_Look.IA_Look'"));
	if (IA_LOOK.Succeeded()) IA_Look = IA_LOOK.Object;

	// IA ComboAttack ����
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_COMBOATTACK
	(TEXT("InputAction'/Game/Input/IA/IA_ComboAttack.IA_ComboAttack'"));
	if (IA_COMBOATTACK.Succeeded()) IA_ComboAttack = IA_COMBOATTACK.Object;

	// IA SprintAttack ����
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SPRINTATTACK
	(TEXT("InputAction'/Game/Input/IA/IA_SprintAttack.IA_SprintAttack'"));
	if (IA_SPRINTATTACK.Succeeded()) IA_SprintAttack = IA_SPRINTATTACK.Object;

	// IA Dodge ����
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_DODGE
	(TEXT("InputAction'/Game/Input/IA/IA_Dodge.IA_Dodge'"));
	if (IA_DODGE.Succeeded()) IA_DodgeAttack = IA_DODGE.Object;

	// IA Heavy Attack ����
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_HEAVY
	(TEXT("InputAction'/Game/Input/IA/IA_Heavy.IA_Heavy'"));
	if (IA_HEAVY.Succeeded()) IA_HeavyAttack = IA_HEAVY.Object;
}

void AMyCharacter::SetSkillValue() {
	// ��ų ���� ���� ���� ����
	FSkillDataStruct* tmp;
	if (IsValid(SkillDataTable)) {
		tmp = SkillDataTable->FindRow<FSkillDataStruct>(FName(TEXT("Halberd")), FString(""));
	}
	
	SkillData.Add("QSkillCoolTime", tmp->QSkillCoolTime);
	SkillData.Add("CSkillCoolTime", tmp->CSkillCoolTime);
	SkillData.Add("MRSkillCoolTime", tmp->MRSkillCoolTime);

	SkillData.Add("QSkillDamage", tmp->QSkillDamage);
	SkillData.Add("CSkillDamage", tmp->CSkillDamage);
	SkillData.Add("MRSkillDamage1", tmp->MRSkillDamage1);
	SkillData.Add("MRSkillDamage2", tmp->MRSkillDamage2);
	SkillData.Add("LSkillDamage1", tmp->LSkillDamage1);
	SkillData.Add("LSkillDamage2", tmp->LSkillDamage2);
	SkillData.Add("LSkillDamage3", tmp->LSkillDamage3);
	SkillData.Add("LSkillDamage4", tmp->LSkillDamage4);

	SkillData.Add("QSkillRange", tmp->QSkillRange);
	SkillData.Add("CSkillRange", tmp->CSkillRange);
	SkillData.Add("MRSkillRange1", tmp->MRSkillRange1);
	SkillData.Add("MRSkillRange2", tmp->MRSkillRange2);
	SkillData.Add("LSkillRange1", tmp->LSkillRange1);
	SkillData.Add("LSkillRange2", tmp->LSkillRange2);
	SkillData.Add("LSkillRange3", tmp->LSkillRange3);
	SkillData.Add("LSkillRange4", tmp->LSkillRange4);

	SkillArea.Add("QSkillBox", tmp->QSkillBox);
	SkillArea.Add("CSkillBox", tmp->CSkillBox);
	SkillArea.Add("MRSkillBox1", tmp->MRSkillBox1);
	SkillArea.Add("MRSkillBox2", tmp->MRSkillBox2);
	SkillArea.Add("LSkillBox1", tmp->LSkillBox1);
	SkillArea.Add("LSkillBox2", tmp->LSkillBox2);
	SkillArea.Add("LSkillBox3", tmp->LSkillBox3);
	SkillArea.Add("LSkillBox4", tmp->LSkillBox4);

	SkillData.Add("QMaxRunTime", tmp->QMaxRunTime);
	SkillData.Add("MRCompleteChargeValue", tmp->MRCompleteChargeValue);
	SkillData.Add("MRMaxChargeValue", tmp->MRMaxChargeValue);

	SkillData.Add("QMP", 30);
	SkillData.Add("CMP", 10);
	SkillData.Add("MRMP", 50);
}

void AMyCharacter::SetCharacterStateValue() {
	FCharacterStateStruct* tmp;
	if (IsValid(CharacterStateTable)) {
		tmp = CharacterStateTable->FindRow<FCharacterStateStruct>(FName(TEXT("Halberd")), FString(""));
	}

	CharacterState.Add("MaxHP", tmp->MaxHP);
	CharacterState.Add("MaxMP", tmp->MaxMP);
	CharacterState.Add("RecoveryHPValue", tmp->RecoveryHPValue);
	CharacterState.Add("RecoveryMPValue", tmp->RecoveryMPValue);
	CharacterState.Add("BaseDamage", tmp->BaseDamage);
	CurrentHP = CharacterState.FindRef("MaxHP");
	CurrentMP = CharacterState.FindRef("MaxMP");
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ��Ʈ�ѷ� ��������
	MyController = Cast<AMyPlayerController>(GetController());

	// ��ų ���� ����
	SetSkillValue();
	// ĳ���� ���� ���� ����
	SetCharacterStateValue();

	// UI ȭ�鿡 �߰�
	if (IsValid(UI_SkillClass)) {
		UI_Skill = Cast<UMySkillWidget>(CreateWidget(GetWorld(), UI_SkillClass));
		UI_Skill->AddToViewport();
	}

	// ���� �Ž� ���� 
	Weapon = GetWorld()->SpawnActor<AMyWeapon>(WeaponCalss);
	if (Weapon) {
		GetMesh()->GetSocketByName("hand_rSocket")->AttachActor(Weapon, GetMesh());
		Weapon->WeoponOwner = this;
	}
	//else UE_LOG(LogTemp, Log, TEXT("Hello"));

	// �� ĳ������ ��Ʈ�ѷ��� �����ͼ� IMC ������ �Ѵ�.
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			SubSystem->AddMappingContext(DefaultContext, 0);
	}
	// ĳ������ �ִϸ��̼��� ���� �����صּ� �ʿ��� �� ȣ���Ѵ�.
	MyAnim = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance()); 
	// ��������Ʈ�� �Լ��� ����Ѵ�.

	// ��Ÿ�ְ� ������ ����Ǵ� ��������Ʈ -> OnMontageEnded�� �⺻������ �ִ� ��������Ʈ�̴�.
	MyAnim->OnMontageEnded.AddDynamic(this, &AMyCharacter::AttackEnded);
	// �޺��� ���� ���� �� ����Ǵ� ��������Ʈ
	MyAnim->OnNextComboCheck.AddLambda([this]()-> void {
		IsAttackAble = false;
		if (IsCombo) {
			IsCombo = 0;
			ComboNum++;
			MyAnim->NextCombo(ComboNum, "Combo");
			switch (ComboNum) {
			case 2:
				ActionState = "ComboAttack2";
				DamageValue = SkillData.FindRef("LSkillDamage2");
				AttackRange = SkillData.FindRef("LSkillRange2");
				AttackBox = SkillArea.FindRef("LSkillBox2");
				break;
			case 3:
				ActionState = "ComboAttack3";
				DamageValue = SkillData.FindRef("LSkillDamage3");
				AttackRange = SkillData.FindRef("LSkillRange3");
				AttackBox = SkillArea.FindRef("LSkillBox3");
				IsCombo = 1;
				break;
			case 4:
				ActionState = "ComboAttack4";
				DamageValue = SkillData.FindRef("LSkillDamage4");
				AttackRange = SkillData.FindRef("LSkillRange4");
				AttackBox = SkillArea.FindRef("LSkillBox4");
				break;
			}
		}
	});
	// ������Ʈ ���� ������ �������� �� ����Ǵ� ��������Ʈ
	MyAnim->OnSprintAttackPossible.AddLambda([this]()-> void {
		UI_Skill->MLActivate();
		ActionState = "SprintAttackPossible";
	});
	// ���� ���� ������ �������� �� ����Ǵ� ��������Ʈ
	MyAnim->OnDodgeAttackCheck.AddLambda([this]()-> void {
		UI_Skill->MLDisable();
		if (ActionState == "DodgeAttackPossible") {
			ActionState = "DodgeAttack";
			MyAnim->JumpToDodgeAttack();
		}
	});
	// ��� ���� ���� ������ �������� �� ����Ǵ� ��������Ʈ
	// ���� ������ ������ 1Ÿ�� �����ϰ� ������ �����Ǹ� 2Ÿ �غ� �Ѵ�.
	MyAnim->OnNoChargeAttackCheck.AddLambda([this]()-> void {
		IsAttackAble = false;
		if (ActionState == "HeavyCharging") {
			if (IsCharge == 0) {
				Weapon->PlayEffect("Charge1");
				IsCharge = 1;
			}
			else if (IsCharge == 1) {
				ActionState = "HeavyAttack";
				MyAnim->JumpToHeavy1();
			}
		}
	});
	// ��� ���� 2Ÿ
	MyAnim->OnChargeAttackCheck.AddLambda([this]()-> void {
		IsAttackAble = false;
		if (IsCharge == 2) {
			ActionState = "HeavyAttack2";
			MyAnim->JumpToHeavy2();
			DamageValue = SkillData.FindRef("MRSkillDamage2") + BaseDamage;
			AttackRange = SkillData.FindRef("MRSkillRange2");
			AttackBox = SkillArea.FindRef("MRSkillBox2");
		}
	});

	// Ÿ�� ������ �����ϴ� ��������Ʈ
	MyAnim->OnAttackAble.AddLambda([this]()->void {
		TArray<struct FHitResult> HitResult;
		// FCollisionQueryParams (�� �浹�� �ĺ��� �±� ��, ������ �浹 ������ �� ���̳�, �浹 ���� ������Ʈ)
		FCollisionQueryParams Params(EName::None, false, this);
		// SweepSingleByChannel(�浹 ����� ������ ����ü, ���� ����, ������ ����, ȸ��, Trace ä�� ����, Trace ���)
		bool IsHit = GetWorld()->SweepMultiByObjectType(
			HitResult,
			GetActorLocation(),
			GetActorLocation() + GetActorForwardVector() * AttackRange,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel3,
			FCollisionShape::MakeBox(AttackBox),
			Params);
		if (IsHit) {
			TArray<FString> BeforeName;
			for (FHitResult SweepActor: HitResult) { // HitResult�� ��� ���ҿ� ���� ���� ����, ���� ��� ����
				AEnemyParent* SweepEnemy = Cast<AEnemyParent>(SweepActor.GetActor());
				if (SweepEnemy && !BeforeName.Contains(SweepEnemy->GetName())) {
					BeforeName.Add(SweepEnemy->GetName());
					Weapon->PlayEffect("Hit", SweepActor.ImpactPoint);
					SweepEnemy->OnDamaged(DamageValue);
				}
			}
		}

#if ENABLE_DRAW_DEBUG
		FVector TraceVector = GetActorForwardVector() * AttackRange;
		FVector Center = GetActorLocation() + TraceVector * 0.5f;
		// �ٶ� ���� ���� ���� BoxExtent(����, ����, �Ÿ�)
		FVector BoxExtent = FVector(AttackBox.Y, AttackBox.X, AttackRange * 0.5f);
		FQuat BoxRotate = FRotationMatrix::MakeFromZ(TraceVector).ToQuat();
		FColor DrawColor = IsHit ? FColor::Green : FColor::Red;
		float DebugTime = 5.0f;

		DrawDebugBox(
			GetWorld(),
			Center,
			BoxExtent,
			BoxRotate,
			DrawColor,
			false,
			DebugTime
		);
#endif
	});

	MyAnim->OnAttackDisable.AddLambda([this]()->void {
		IsAttackAble = false;
	});

	MyAnim->OnPlayEffect.AddLambda([this]()->void {
		Weapon->PlayEffect("Charge2");
	});
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// �뽬 ������ ��ġ�� ª�Ƽ� ���� �������� ��ġ�� �÷ȴ�.
	if (ActionState == "SprintAttack") {
		FVector FinalPosition = FMath::VInterpTo(GetActorLocation(), TargetPosition, DeltaTime, 5);
		SetActorLocation(FinalPosition);
	}
	// ������ ��Ÿ�ַ� ����Ͽ� ������ ������ �����Ͽ��� ���� �߿��� �������� ������ �ʵ��� ����
	else if (ActionState == "Jump") {
		if (GetVelocity().Z == 0) ActionState = "Land";
		MyAnim->JumpToLanding();
	}
	if ((ActionState == "Jump" || ActionState == "Idle") && CurrentMP < CharacterState.FindRef("MaxMP") && IsRecoverMP == 0) {
		IsRecoverMP = 1;
		GetWorldTimerManager().SetTimer(RecoverMPTimerHandle, this, &AMyCharacter::NaturalRecoverMP, 1, true, 5);
	}
	//UE_LOG(LogTemp, Log, TEXT("%s"), IsAttackAble ? TEXT("true") : TEXT("false"));
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Input Action�� ���ε�
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &AMyCharacter::JumpAction);
		EnhancedInputComponent->BindAction(IA_CameraZoom, ETriggerEvent::Triggered, this, &AMyCharacter::CameraZoom);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &AMyCharacter::MoveEnd);
		EnhancedInputComponent->BindAction(IA_Dash, ETriggerEvent::Triggered, this, &AMyCharacter::DashStart);
		EnhancedInputComponent->BindAction(IA_Dash, ETriggerEvent::Completed, this, &AMyCharacter::DashEnd);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		EnhancedInputComponent->BindAction(IA_ComboAttack, ETriggerEvent::Started, this, &AMyCharacter::ComboAttack);
		EnhancedInputComponent->BindAction(IA_SprintAttack, ETriggerEvent::Started, this, &AMyCharacter::SprintAttack);
		EnhancedInputComponent->BindAction(IA_DodgeAttack, ETriggerEvent::Started, this, &AMyCharacter::Dodge);
		EnhancedInputComponent->BindAction(IA_HeavyAttack, ETriggerEvent::Triggered, this, &AMyCharacter::HeavyAttack);
		EnhancedInputComponent->BindAction(IA_HeavyAttack, ETriggerEvent::Completed, this, &AMyCharacter::HeavyEnd);
	}

}







// ���ε� �� IA�� ���⼭ �۾�

// �����̴� IA
void AMyCharacter::Move(const FInputActionValue& Value) {
	if (ActionState != "Idle" && ActionState != "Jump") return;
	// 0���Ϳ� �Է� Y�� * ���� ���� + �Է� X�� * ������ ���� ���� ���� �̵��ؾ� �� ������ ���ϰ� Movement�� �����ش�.
	FVector Direction = FVector::ZeroVector;
	int Y = Value.Get<FVector2D>().Y;
	int X = Value.Get<FVector2D>().X;

	// Move Value�� �ȴ� Blend Space���� ���޵� ���̴�.
	MoveValue.X = X * 300 * DashValue;
	MoveValue.Y = Y * 300 * DashValue;

	Direction += GetCapsuleComponent()->GetForwardVector() * Y;
	Direction += GetCapsuleComponent()->GetRightVector() * X;

	AddMovementInput(Direction, 1);
}

void AMyCharacter::MoveEnd(const FInputActionValue& Value) {
	MoveValue.X = 0;
	MoveValue.Y = 0;
}

// �޸���
void AMyCharacter::DashStart(const FInputActionValue& Value) {
	// ĳ������ �⺻ �ӵ��� �ٲپ� �� ������ �޸��� �Ѵ�.
	DashValue = 2;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AMyCharacter::DashEnd(const FInputActionValue& Value) {
	DashValue = 1;
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

// ����
void AMyCharacter::JumpAction(const FInputActionValue& Value) {
	if (ActionState != "Idle") return;
	ActionState = "Jump";
	MyAnim->PlayMongtage("Jump", AttackSpeed);
	Jump();// ������ �𸮾󿡼� �Լ��� ������ ����.
}







// �þ� IA

// ī�޶� ȸ��
void AMyCharacter::Look(const FInputActionValue& Value) {
	if (ActionState != "Idle" && ActionState != "Sprint" && ActionState != "SprintAttackPossible"
		&& ActionState != "HeavyCharging") return;
	AddControllerYawInput(Value.Get<FVector2D>().X * CameraRotateScale);
	AddControllerPitchInput(Value.Get<FVector2D>().Y * CameraRotateScale);
}

// ī�޶� ���ξƿ�
void AMyCharacter::CameraZoom(const FInputActionValue& Value) {
	SpringArm->TargetArmLength = FMath::Clamp(Value.Get<float>() * 30 + SpringArm->TargetArmLength, CameraZoomMin, CameraZoomMax);
}







// �������ͽ� ���� �Լ�

// HP ���� �Լ�
void AMyCharacter::DiffHP(float _HP) {
	float _MaxHP = CharacterState.FindRef("MaxHP");
	if (_HP < 0) CurrentHP += _HP + BaseGuard;
	else {
		CurrentHP += _HP;
		if (CurrentHP > _MaxHP) {
			CurrentHP = _MaxHP;
		}
	}
	UI_Skill->HPBar->SetPercent(CurrentHP / _MaxHP);
}
// MP ���� �Լ�
void AMyCharacter::DiffMP(float _MP) {
	float _MaxMP = CharacterState.FindRef("MaxMP");
	IsRecoverMP = 0;
	GetWorldTimerManager().ClearTimer(RecoverMPTimerHandle);
	CurrentMP += _MP;
	if (CurrentMP > _MaxMP) {
		CurrentMP = _MaxMP;
	}
	UI_Skill->MPBar->SetPercent(CurrentMP / CharacterState.FindRef("MaxMP"));
}

// HP �ڿ� ȸ�� �Լ�
void AMyCharacter::NaturalRecoverHP() {
	float _MaxHP = CharacterState.FindRef("MaxHP");
	CurrentHP += CharacterState.FindRef("RecoveryHPValue");
	if (CurrentHP > _MaxHP) {
		CurrentHP = _MaxHP;
	}
	UI_Skill->HPBar->SetPercent(CurrentHP / _MaxHP);
}

// MP �ڿ� ȸ�� �Լ�
void AMyCharacter::NaturalRecoverMP() {
	float _MaxMP = CharacterState.FindRef("MaxMP");
	CurrentMP += CharacterState.FindRef("RecoveryMPValue");
	if (CurrentMP > _MaxMP) {
		CurrentMP = _MaxMP;
	}
	UI_Skill->MPBar->SetPercent(CurrentMP / _MaxMP);
}





// ���� IA

// �⺻ �޺� ����
void AMyCharacter::ComboAttack(const FInputActionValue& Value) {
	if (ActionState == "Idle") {
		ActionState = "ComboAttack1";
		MyAnim->PlayMongtage("Combo", AttackSpeed);
		DamageValue = SkillData.FindRef("LSkillDamage1") + BaseDamage;
		AttackRange = SkillData.FindRef("LSkillRange1");
		AttackBox = SkillArea.FindRef("LSkillBox1");
	}
	else if (ActionState == "SprintAttackPossible") {
		QSkillRunValue = 0.f;
		UI_Skill->MLDisable();
		UI_Skill->ChargeBarDisable();
		GetWorldTimerManager().ClearTimer(QSkillRunTimerHandle);
		ActionState = "SprintAttack";
		MyAnim->NextCombo(2, "Sprint");
		TargetPosition = GetActorLocation() + GetCapsuleComponent()->GetForwardVector() * 500;
		DamageValue = SkillData.FindRef("QSkillDamage") + BaseDamage;
		AttackRange = SkillData.FindRef("QSkillRange");
		AttackBox = SkillArea.FindRef("QSkillBox");
	}
	else if (ActionState == "Dodge") {
		ActionState = "DodgeAttackPossible";
		DamageValue = SkillData.FindRef("CSkillDamage") + BaseDamage;
		AttackRange = SkillData.FindRef("CSkillRange");
		AttackBox = SkillArea.FindRef("CSkillBox");
	}
	else {
		IsCombo = 1;
	}
}

// ������Ʈ ����
void AMyCharacter::SprintAttack(const FInputActionValue& Value) {
	if (ActionState == "Idle" && QSkillCoolValue == 0 && CurrentMP >= SkillData.FindRef("QMP")) {
		DiffMP(-SkillData.FindRef("QMP"));
		UI_Skill->ChargeBarActivate("Q");
		UI_Skill->IconSizeDown("Q");
		GetWorldTimerManager().SetTimer(QSkillTimerHandle, this, &AMyCharacter::QSkillCoolTime, SkillCoolRate, true, 0);
		GetWorldTimerManager().SetTimer(QSkillRunTimerHandle, this, &AMyCharacter::QSkillRunTime, SkillCoolRate, true, 0);
		ActionState = "Sprint";
		MyAnim->PlayMongtage("Sprint", AttackSpeed);
		CameraRotateScale = 0.2f;
	}
}

// �Ĺ����� ���� ȸ�� �� ���� ���� ����
void AMyCharacter::Dodge(const FInputActionValue& Value) {
	if (ActionState == "Idle" && CSkillCoolValue == 0 && CurrentMP >= SkillData.FindRef("CMP")) {
		DiffMP(-SkillData.FindRef("CMP"));
		UI_Skill->MLActivate();
		UI_Skill->IconSizeDown("C");
		GetWorldTimerManager().SetTimer(CSkillTimerHandle, this, &AMyCharacter::CSkillCoolTime, SkillCoolRate, true, 0);
		ActionState = "Dodge";
		MyAnim->PlayMongtage("Dodge", AttackSpeed);
	}
}

// ���� ����, ������ ���� �� ���ϰ� ������ �ִ�.
void AMyCharacter::HeavyAttack(const FInputActionValue& Value) {
	if (ActionState == "Idle" && MRSkillCoolValue == 0 && CurrentMP >= SkillData.FindRef("MRMP")) {
		DiffMP(-SkillData.FindRef("MRMP"));
		UI_Skill->ChargeBarActivate("MR");
		UI_Skill->IconSizeDown("MR");
		GetWorldTimerManager().SetTimer(MRSkillTimerHandle, this, &AMyCharacter::MRSkillCoolTime, SkillCoolRate, true, 0);
		GetWorldTimerManager().SetTimer(MRSkillChargeTimerHandle, this, &AMyCharacter::MRSkillChargeTime, SkillCoolRate, true, 0);
		CameraRotateScale = 0.1f;
		ActionState = "HeavyCharging";
		MyAnim->PlayMongtage("Heavy", AttackSpeed);
		DamageValue = SkillData.FindRef("MRSkillDamage1") + BaseDamage;
		AttackRange = SkillData.FindRef("MRSkillRange1");
		AttackBox = SkillArea.FindRef("MRSkillBox1");
	}
}

void AMyCharacter::HeavyEnd(const FInputActionValue& Value) {
	UI_Skill->ChargeBarDisable();
	GetWorldTimerManager().ClearTimer(MRSkillChargeTimerHandle);
	if (IsCharge == 0 && ActionState == "HeavyCharging") IsCharge = 1;
	else if (IsCharge >= 1 && ActionState == "HeavyCharging") {
		ActionState = "HeavyAttack";
		MyAnim->JumpToHeavy1();
	}
}

// ��Ÿ�ְ� ������ ����Ǵ� �Լ� �׻� ĳ������ ���¿� ���õ� �͵��� �ʱ�ȭ �Ѵ�.
void AMyCharacter::AttackEnded(UAnimMontage* Montage, bool bInterrupted) {
	IsCombo = 0;
	ActionState = "Idle";
	ComboNum = 1;
	ChargeValue = 0;
	CameraRotateScale = 1.f;
	IsCharge = 0;
}

// ��Ÿ�� �Լ�

void AMyCharacter::QSkillCoolTime() {
	QSkillCoolValue += SkillCoolRate;
	float MaxTime = SkillData.FindRef("QSkillCoolTime") * CoolTimeDown;
	UI_Skill->QSkill->SetPercent((MaxTime - QSkillCoolValue) / MaxTime);
	if (QSkillCoolValue >= MaxTime) {
		QSkillCoolValue = 0.f;
		UI_Skill->IconSizeUp("Q");
		GetWorldTimerManager().ClearTimer(QSkillTimerHandle);
	}
}

void AMyCharacter::CSkillCoolTime() {
	CSkillCoolValue += SkillCoolRate;
	float MaxTime = SkillData.FindRef("CSkillCoolTime") * CoolTimeDown;
	UI_Skill->CSkill->SetPercent((MaxTime - CSkillCoolValue) / MaxTime);
	if (CSkillCoolValue >= MaxTime) {
		CSkillCoolValue = 0.f;
		UI_Skill->IconSizeUp("C");
		GetWorldTimerManager().ClearTimer(CSkillTimerHandle);
	}
}

void AMyCharacter::MRSkillCoolTime() {
	MRSkillCoolValue += SkillCoolRate;
	float MaxTime = SkillData.FindRef("MRSkillCoolTime") * CoolTimeDown;
	UI_Skill->MRSkill->SetPercent((MaxTime - MRSkillCoolValue) / MaxTime);
	if (MRSkillCoolValue >= MaxTime) {
		MRSkillCoolValue = 0.f;
		UI_Skill->IconSizeUp("MR");
		GetWorldTimerManager().ClearTimer(MRSkillTimerHandle);
	}
}

// Q��ų �޸��� �Լ�

void AMyCharacter::QSkillRunTime() {
	QSkillRunValue += SkillCoolRate;
	float MaxTime = SkillData.FindRef("QMaxRunTime") * CoolTimeDown;
	UI_Skill->ChargeBar->SetPercent((MaxTime - QSkillRunValue) / MaxTime);
	if (QSkillRunValue >= MaxTime) {
		MyAnim->StopMontage("Sprint");
		QSkillRunValue = 0;
		UI_Skill->ChargeBarDisable();
		UI_Skill->MLDisable();
		GetWorldTimerManager().ClearTimer(QSkillRunTimerHandle);
	}
}

// MR ��ų ��¡ �Լ�
void AMyCharacter::MRSkillChargeTime() {
	ChargeValue += SkillCoolRate;
	float CompleteChargeTime = SkillData.FindRef("MRCompleteChargeValue");
	float MaxChargeValue = SkillData.FindRef("MRMaxChargeValue");
	UI_Skill->ChargeBar->SetPercent(ChargeValue / CompleteChargeTime);
	if (ChargeValue >= CompleteChargeTime && ChargeValue < MaxChargeValue) {
		IsCharge = 2;
	}
	else if (ChargeValue >= MaxChargeValue) {
		ActionState = "HeavyAttack";
		MyAnim->JumpToHeavy1();
		UI_Skill->ChargeBarDisable();
		GetWorldTimerManager().ClearTimer(MRSkillChargeTimerHandle);
	}
}