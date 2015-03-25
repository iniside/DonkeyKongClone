// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong.h"

#include "DKPlayerController.h"
#include "DonkeyKongGameMode.h"
#include "DKGameInstance.h"

#include "LevelSupport/DKLevelMaster.h"
#include "LevelSupport/DKLadder.h"

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

	bHaveClimbed = false;
	bHaveJumped = false;
}

void ADonkeyKongCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (auto It = TActorIterator<ADKLevelMaster>(GetWorld()); It; ++It)
	{
		MasterLevel = *It;
		break;
	}
	for (auto Iter = LadderToTrace.CreateConstIterator(); Iter; ++Iter)
	{
		const ECollisionChannel & Channel = (*Iter);
		if (FCollisionObjectQueryParams::IsValidObjectQuery(Channel))
		{
			LadderPrams.AddObjectTypesToQuery(Channel);
		}
	}

	GameMode = Cast<ADonkeyKongGameMode>(GetWorld()->GetAuthGameMode());
	GameInstance = Cast<UDKGameInstance>(GetGameInstance());
}

void ADonkeyKongCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	//make box at last location
	//in case of falling, in location where pawn last standed.
	//in case of jumping it will be at about jump apex.
	FBox lastBox(LastLocation-100, LastLocation+100);
	//and box at location where pawn landed.
	FBox currentBox(GetActorLocation() - 100, GetActorLocation() + 100);

	if (currentBox.Intersect(lastBox))
	{

	}
	else
	{
		CharacterDied();
	}
}
void ADonkeyKongCharacter::Falling()
{
	LastLocation = GetActorLocation();
}
void ADonkeyKongCharacter::BeginDestroy()
{
	if (EquipedWeapon)
	{
		EquipedWeapon->Destroy();
	}
	Super::BeginDestroy();
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
	InputComponent->BindAction("CheckForLadder", IE_Pressed, this, &ADonkeyKongCharacter::InputLookForLadder);

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

void ADonkeyKongCharacter::InputLookForLadder()
{
	if (!bIsClimbing)
	{
		FVector StartTrace = GetActorLocation() + FVector(150, 0, 0);
		FVector EndTrace = StartTrace + FVector(-1, 0, 0) * 100;

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		FHitResult hit;
		GetWorld()->LineTraceSingle(hit, StartTrace, EndTrace, Params, LadderPrams);

		if (hit.Actor.IsValid())
		{
			if (ADKLadder* Ladder = Cast<ADKLadder>(hit.Actor.Get()))
			{
				SetActorLocation(hit.Location);
				bIsClimbing = true;
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
				CurrentLadder = Ladder;
			}
		}
	}
}

// Input
//////////////////////////////////////////////////////////////////////////


void ADonkeyKongCharacter::ClimbFinish(const FVector& LeaveLedderLocation, class ADKLadder* Ladder)
{
	if (Ladder == CurrentLadder)
	{
		TeleportTo(LeaveLedderLocation, FRotator(0, 0, 0));
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		bIsClimbing = false;
		bHaveClimbed = true;
	}
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