// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong.h"

#include "DKPlayerController.h"
#include "DonkeyKongGameMode.h"
#include "DKGameInstance.h"

#include "LevelSupport/DKLevelMaster.h"
#include "Enemies/DKEnemy.h"

#include "DKWeapon.h"

#include "DonkeyKongCharacter.h"

ADonkeyKongCharacter::ADonkeyKongCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	bIsClimbing = false;
	ClimbingDirection = 0;

	EnemyDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyDetection"));
	EnemyDetection->AttachTo(RootComponent);
	EnemyDetection->OnComponentBeginOverlap.AddDynamic(this, &ADonkeyKongCharacter::EnemyDetection_BeginOverlap);

	WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	WeaponAttachPoint->AttachTo(RootComponent);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADonkeyKongCharacter::Capsule_BeginOverlap);
}

void ADonkeyKongCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (auto It = TActorIterator<ADKLevelMaster>(GetWorld()); It; ++It)
	{
		MasterLevel = *It;
		break;
	}


	GameMode = Cast<ADonkeyKongGameMode>(GetWorld()->GetAuthGameMode());
	GameInstance = Cast<UDKGameInstance>(GetGameInstance());
}

void ADonkeyKongCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	DKPC = Cast<ADKPlayerController>(NewController);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADonkeyKongCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &ADonkeyKongCharacter::MoveRight);
	InputComponent->BindAxis("Climb", this, &ADonkeyKongCharacter::Climb);
}

void ADonkeyKongCharacter::MoveRight(float Value)
{
	// add movement in that direction
	if (!bIsClimbing)
	{
		AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
	}
}

void ADonkeyKongCharacter::Climb(float Value)
{
	ClimbingDirection = Value;
	if (bIsClimbing)
	{
		FVector Move = ClimbDirection * Value;
		AddActorLocalOffset(Move);
		UnEquipWeapon();
	}
	
}

// Input
//////////////////////////////////////////////////////////////////////////


void ADonkeyKongCharacter::ClimbFinish(const FVector& LeaveLedderLocation)
{
	TeleportTo(LeaveLedderLocation, FRotator(0, 0, 0));
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bIsClimbing = false;
}

void ADonkeyKongCharacter::EnemyDetection_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//don't allow to score when player is on ladder.
	if (bIsClimbing || !DKPC)
		return;

	//we also need cooldown, for player scoring (I think?)
	//to prevent player from constatly jumping over enemies and scoring.
	//at least it seems to work this way.
	if (ADKEnemy* Enemy = Cast<ADKEnemy>(OtherActor))
	{
		if (Enemy == LastEnemy)
			return;
		LastEnemy = Enemy;
		DKPC->AddScore(Enemy->GetActorLocation(), Enemy->GetScoreForJumping());
	}
}

void ADonkeyKongCharacter::Capsule_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADKEnemy* Enemy = Cast<ADKEnemy>(OtherActor))
	{
		CharacterDied();
	}
}

void ADonkeyKongCharacter::CharacterDied()
{
	GameInstance->SubtractPlayerLife();

	GameMode->PlayerDied(this);
	DKPC->PlayerDied();
	DKPC->Spectate();

	Destroy();
}


void ADonkeyKongCharacter::EquipWeapon(class ADKWeapon* WeaponIn)
{
	if (EquipedWeapon)
	{
		UnEquipWeapon();
		EquipedWeapon = WeaponIn;
	}
	else
	{
		EquipedWeapon = WeaponIn;
	}
	EquipedWeapon->AttachRootComponentTo(WeaponAttachPoint, NAME_None, EAttachLocation::SnapToTarget);
	EquipedWeapon->ActivateWeapon(this);
}

void ADonkeyKongCharacter::UnEquipWeapon()
{
	if (EquipedWeapon)
		EquipedWeapon->Destroy();
}

bool ADonkeyKongCharacter::HaveWeapon()
{
	if (EquipedWeapon)
	{
		return true;
	}
	else
	{
		return false;	
	}
}