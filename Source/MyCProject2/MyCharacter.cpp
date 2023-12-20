// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "MyAnimInstance.h"
#include "MyWeapon.h"
#include "MyPlayerController.h"
#include "MySkillWidget.h"
#include "SkillDataStruct.h"
#include "CharacterStateStruct.h"
#include "GameFramework/SpringArmComponent.h"//SpringArm 사용하기 위해
#include "Camera/CameraComponent.h"//Camera 사용하기 위해
#include "Components/CapsuleComponent.h"//CapsuleComponent 사용하기 위해
#include "EnhancedInputComponent.h" // 밑 3줄까지 Enhanced Input을 사용하기 위한 헤더
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h" // CharacterMovement를 사용하기 위해
#include "Engine/SkeletalMeshSocket.h" // 소캣을 사용하기 위해
#include "Math/UnrealMathUtility.h" // 언리얼에서 제공하는 수학 함수들
#include "Engine/DataTable.h" // 데이터 테이블 사용
#include "Components/ProgressBar.h" // ProgressBar 사용
#include "EnemyParent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 변수 설정/////////////////////

	// 점프 변수
	// GetCharacterMovement()->JumpZVelocity = 500.0f;	// 점프 높이.
	// JumpMaxCount = 2;								// 한번에 점프 가능한 횟수. 1이 기본 값.
	// JumpMaxHoldTime = 3.0f;							// 점프를 유지하는 시간
	// 
	// 움직임 변수
	DashValue = 1;										// 1이면 걸어가고 2면 뛴다									
	GetCharacterMovement()->MaxWalkSpeed = 300;			// 초기 걸음 속도
	//
	// 컨트롤러
	// 
	// 공격 변수
	ActionState = "Idle";								// 현재 캐릭터의 상태를 표현
														// 현재 캐릭터의 상태를 통해 여러 행동이 서로 간섭하지 않도록 하였다.
	ComboNum = 1;										// 콤보 공격할 때 몇번째 콤보인지 나타낸다.
	IsCombo = 0;										// 콤보 공격 키를 감지해서 다음 콤보 공격을 할 지 판단한다.
	ChargeValue = 0;									// 헤비 공격의 차지 정도를 표현하는 수치
	IsCharge = 0;										// 차지가 만족할 만큼 됐는지를 판단하여 다음 헤비 공격을 판단한다.
	SkillCoolRate = 0.01f;								// 스킬 쿨타임 돌리는 함수를 몇초마다 한번씩 실행을 할 것인가
	DamageValue = 0.0f;
														// 
	// 카메라 변수
	CameraZoomMin = 150.f;								// 휠업다운을 통한 줌인아웃의 최소 및 최대 길이
	CameraZoomMax = 800.f;
	CameraRotateScale = 1.f;							// 특정 스킬 중에는 카메라 회전 속도를 조절하기 위한 변수
	//
	// 업그레이드 변수
	AttackSpeed = 1.0f;
	CoolTimeDown = 1.0f;
	BaseDamage = 0.0f;
	BaseGuard = 0.0f;
	////////////////////////////////

	// Component 생성
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Component 붙이기
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	// Component initail transtrom 설정
	SpringArm->TargetArmLength = 500.f;
	SpringArm->TargetOffset.Z = 100.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	// 카메라 움직이기 사전 작업
	SpringArm->bUsePawnControlRotation = true; // 이걸 해줘야 Look함수의 AddController~Input이 먹힌다.

	// 캐릭터 매쉬 생성
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(
		TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Golden.SK_CharM_Golden'"));
	if (CharacterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
		//GetArrowComponent()->SetupAttachment(GetMesh());
	}

	// 충돌 설정
	GetMesh()->SetCollisionProfileName("PlayerMesh");
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetNotifyRigidBodyCollision(true);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(false);

	// 스킬 데이터 테이블 생성
	static ConstructorHelpers::FObjectFinder<UDataTable> SKILL_DATA_TABLE(
		TEXT("/Script/Engine.DataTable'/Game/DataTable/SkillDataTable'"));
	if (SKILL_DATA_TABLE.Succeeded()) {
		SkillDataTable = SKILL_DATA_TABLE.Object;
	}

	// 캐릭터 상태 변수 데이터 테이블 생성
	static ConstructorHelpers::FObjectFinder<UDataTable> CHARACTER_STATE_TABLE(
		TEXT("/Script/Engine.DataTable'/Game/DataTable/CharacterStateTable'"));
	if (CHARACTER_STATE_TABLE.Succeeded()) {
		CharacterStateTable = CHARACTER_STATE_TABLE.Object;
	}

	// UI 생성
	static ConstructorHelpers::FClassFinder<UMySkillWidget> UI_SKILLWIDGET(
		TEXT("WidgetBlueprint'/Game/UI/UI_SkillWidget'"));
	if (UI_SKILLWIDGET.Succeeded()) {
		UI_SkillClass = UI_SKILLWIDGET.Class;
	}
	
	// 무기 생성
	static ConstructorHelpers::FClassFinder<AMyWeapon> MY_WEAPON(
		TEXT("Class'/Script/MyCProject2.MyWeapon'"));
	if (MY_WEAPON.Succeeded()) WeaponCalss = MY_WEAPON.Class;

	// 애니메이션 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> MYANIM(
		TEXT("AnimBlueprint'/Game/InfinityBladeWarriors/Character/CompleteCharacters/ABP/ABP_MyCharacter'"));
	if (MYANIM.Succeeded()) GetMesh()->SetAnimInstanceClass(MYANIM.Class);

	// IMC 생성
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>IMC_MYCHARACTER
	(TEXT("InputMappingContext'/Game/Input/IMC_MyCharacter.IMC_MyCharacter'"));
	if (IMC_MYCHARACTER.Succeeded()) DefaultContext = IMC_MYCHARACTER.Object;

	// IA Move 생성
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_MOVE
	(TEXT("InputAction'/Game/Input/IA/IA_Move.IA_Move'"));
	if (IA_MOVE.Succeeded()) IA_Move = IA_MOVE.Object;

	// IA Jump 생성
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_JUMP
	(TEXT("InputAction'/Game/Input/IA/IA_Jump.IA_Jump'"));
	if (IA_JUMP.Succeeded()) IA_Jump = IA_JUMP.Object;

	// IA CameraZoom 생성
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_CAMERAZOOM
	(TEXT("InputAction'/Game/Input/IA/IA_CameraZoom.IA_CameraZoom'"));
	if (IA_CAMERAZOOM.Succeeded()) IA_CameraZoom = IA_CAMERAZOOM.Object;

	// IA Dash 생성
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_DASH
	(TEXT("InputAction'/Game/Input/IA/IA_Dash.IA_Dash'"));
	if (IA_DASH.Succeeded()) IA_Dash = IA_DASH.Object;

	// IA Look 생성
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_LOOK
	(TEXT("InputAction'/Game/Input/IA/IA_Look.IA_Look'"));
	if (IA_LOOK.Succeeded()) IA_Look = IA_LOOK.Object;

	// IA ComboAttack 생성
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_COMBOATTACK
	(TEXT("InputAction'/Game/Input/IA/IA_ComboAttack.IA_ComboAttack'"));
	if (IA_COMBOATTACK.Succeeded()) IA_ComboAttack = IA_COMBOATTACK.Object;

	// IA SprintAttack 생성
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SPRINTATTACK
	(TEXT("InputAction'/Game/Input/IA/IA_SprintAttack.IA_SprintAttack'"));
	if (IA_SPRINTATTACK.Succeeded()) IA_SprintAttack = IA_SPRINTATTACK.Object;

	// IA Dodge 생성
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_DODGE
	(TEXT("InputAction'/Game/Input/IA/IA_Dodge.IA_Dodge'"));
	if (IA_DODGE.Succeeded()) IA_DodgeAttack = IA_DODGE.Object;

	// IA Heavy Attack 생성
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_HEAVY
	(TEXT("InputAction'/Game/Input/IA/IA_Heavy.IA_Heavy'"));
	if (IA_HEAVY.Succeeded()) IA_HeavyAttack = IA_HEAVY.Object;
}

void AMyCharacter::SetSkillValue() {
	// 스킬 관련 고정 변수 설정
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

	// 컨트롤러 가져오기
	MyController = Cast<AMyPlayerController>(GetController());

	// 스킬 변수 설정
	SetSkillValue();
	// 캐릭터 상태 변수 설정
	SetCharacterStateValue();

	// UI 화면에 추가
	if (IsValid(UI_SkillClass)) {
		UI_Skill = Cast<UMySkillWidget>(CreateWidget(GetWorld(), UI_SkillClass));
		UI_Skill->AddToViewport();
	}

	// 무기 매쉬 생성 
	Weapon = GetWorld()->SpawnActor<AMyWeapon>(WeaponCalss);
	if (Weapon) {
		GetMesh()->GetSocketByName("hand_rSocket")->AttachActor(Weapon, GetMesh());
		Weapon->WeoponOwner = this;
	}
	//else UE_LOG(LogTemp, Log, TEXT("Hello"));

	// 이 캐릭터의 컨트롤러를 가져와서 IMC 맵핑을 한다.
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			SubSystem->AddMappingContext(DefaultContext, 0);
	}
	// 캐릭터의 애니메이션을 따로 저장해둬서 필요할 때 호출한다.
	MyAnim = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance()); 
	// 델리게이트에 함수를 등록한다.

	// 몽타주가 끝나면 실행되는 델리게이트 -> OnMontageEnded는 기본적으로 있는 델리게이트이다.
	MyAnim->OnMontageEnded.AddDynamic(this, &AMyCharacter::AttackEnded);
	// 콤보를 감지 했을 때 실행되는 델리게이트
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
	// 스프린트 도중 공격을 감지했을 때 실행되는 델리게이트
	MyAnim->OnSprintAttackPossible.AddLambda([this]()-> void {
		UI_Skill->MLActivate();
		ActionState = "SprintAttackPossible";
	});
	// 닷지 도중 공격을 감지했을 때 실행되는 델리게이트
	MyAnim->OnDodgeAttackCheck.AddLambda([this]()-> void {
		UI_Skill->MLDisable();
		if (ActionState == "DodgeAttackPossible") {
			ActionState = "DodgeAttack";
			MyAnim->JumpToDodgeAttack();
		}
	});
	// 헤비 어택 차지 정도를 감지했을 때 실행되는 델리게이트
	// 차지 정도가 낮으면 1타만 실행하고 차지가 만족되면 2타 준비를 한다.
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
	// 헤비 공격 2타
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

	// 타격 유무를 감지하는 델리게이트
	MyAnim->OnAttackAble.AddLambda([this]()->void {
		TArray<struct FHitResult> HitResult;
		// FCollisionQueryParams (이 충돌을 식별할 태그 값, 복잡한 충돌 연산을 할 것이냐, 충돌 무시 오브젝트)
		FCollisionQueryParams Params(EName::None, false, this);
		// SweepSingleByChannel(충돌 결과를 저장할 구조체, 시작 지점, 끝나는 지점, 회전, Trace 채널 설정, Trace 모양)
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
			for (FHitResult SweepActor: HitResult) { // HitResult의 모든 원소에 대해 루프 진행, 범위 기반 루프
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
		// 바라 보는 방향 기준 BoxExtent(가로, 높이, 거리)
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
	// 대쉬 공격의 리치가 짧아서 선형 보간으로 리치를 늘렸다.
	if (ActionState == "SprintAttack") {
		FVector FinalPosition = FMath::VInterpTo(GetActorLocation(), TargetPosition, DeltaTime, 5);
		SetActorLocation(FinalPosition);
	}
	// 점프를 몽타주로 재생하여 점프와 착지를 구분하였고 착지 중에는 움직임이 먹히지 않도록 설정
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

	// Input Action을 바인딩
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







// 바인딩 한 IA를 여기서 작업

// 움직이는 IA
void AMyCharacter::Move(const FInputActionValue& Value) {
	if (ActionState != "Idle" && ActionState != "Jump") return;
	// 0벡터에 입력 Y값 * 정면 방향 + 입력 X값 * 오른쪽 방향 값을 통해 이동해야 할 방향을 구하고 Movement에 더해준다.
	FVector Direction = FVector::ZeroVector;
	int Y = Value.Get<FVector2D>().Y;
	int X = Value.Get<FVector2D>().X;

	// Move Value는 걷는 Blend Space에게 전달될 값이다.
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

// 달리기
void AMyCharacter::DashStart(const FInputActionValue& Value) {
	// 캐릭터의 기본 속도를 바꾸어 더 빠르게 달리게 한다.
	DashValue = 2;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AMyCharacter::DashEnd(const FInputActionValue& Value) {
	DashValue = 1;
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

// 점프
void AMyCharacter::JumpAction(const FInputActionValue& Value) {
	if (ActionState != "Idle") return;
	ActionState = "Jump";
	MyAnim->PlayMongtage("Jump", AttackSpeed);
	Jump();// 점프는 언리얼에서 함수를 구현해 놨다.
}







// 시야 IA

// 카메라 회전
void AMyCharacter::Look(const FInputActionValue& Value) {
	if (ActionState != "Idle" && ActionState != "Sprint" && ActionState != "SprintAttackPossible"
		&& ActionState != "HeavyCharging") return;
	AddControllerYawInput(Value.Get<FVector2D>().X * CameraRotateScale);
	AddControllerPitchInput(Value.Get<FVector2D>().Y * CameraRotateScale);
}

// 카메라 줌인아웃
void AMyCharacter::CameraZoom(const FInputActionValue& Value) {
	SpringArm->TargetArmLength = FMath::Clamp(Value.Get<float>() * 30 + SpringArm->TargetArmLength, CameraZoomMin, CameraZoomMax);
}







// 스테이터스 관련 함수

// HP 조절 함수
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
// MP 조절 함수
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

// HP 자연 회복 함수
void AMyCharacter::NaturalRecoverHP() {
	float _MaxHP = CharacterState.FindRef("MaxHP");
	CurrentHP += CharacterState.FindRef("RecoveryHPValue");
	if (CurrentHP > _MaxHP) {
		CurrentHP = _MaxHP;
	}
	UI_Skill->HPBar->SetPercent(CurrentHP / _MaxHP);
}

// MP 자연 회복 함수
void AMyCharacter::NaturalRecoverMP() {
	float _MaxMP = CharacterState.FindRef("MaxMP");
	CurrentMP += CharacterState.FindRef("RecoveryMPValue");
	if (CurrentMP > _MaxMP) {
		CurrentMP = _MaxMP;
	}
	UI_Skill->MPBar->SetPercent(CurrentMP / _MaxMP);
}





// 공격 IA

// 기본 콤보 공격
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

// 스프린트 시작
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

// 후방으로 빠른 회피 및 공격 연계 가능
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

// 강한 공격, 차지를 통해 더 강하게 때릴수 있다.
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

// 몽타주가 끝나면 실행되는 함수 항상 캐릭터의 상태와 관련된 것들을 초기화 한다.
void AMyCharacter::AttackEnded(UAnimMontage* Montage, bool bInterrupted) {
	IsCombo = 0;
	ActionState = "Idle";
	ComboNum = 1;
	ChargeValue = 0;
	CameraRotateScale = 1.f;
	IsCharge = 0;
}

// 쿨타임 함수

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

// Q스킬 달리기 함수

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

// MR 스킬 차징 함수
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