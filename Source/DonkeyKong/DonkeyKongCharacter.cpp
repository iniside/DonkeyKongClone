// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong.h"
#include "DKLevelMaster.h"
#include "DKPlayerController.h"
#include "DKEnemy.h"
#include "DonkeyKongGameMode.h"
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

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

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

	DKPC = Cast<ADKPlayerController>(GetController());
	
	GameMode = Cast<ADonkeyKongGameMode>(GetWorld()->GetAuthGameMode());
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


	InputComponent->BindTouch(IE_Pressed, this, &ADonkeyKongCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ADonkeyKongCharacter::TouchStopped);
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
		//AddMovementInput(FVector(0.f, 0.f, 1.f), Value);
	}
}

void ADonkeyKongCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ADonkeyKongCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

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
	if (bIsClimbing)
		return;
 	if (ADKEnemy* Enemy = Cast<ADKEnemy>(OtherActor))
	{
		if (Enemy == LastEnemy)
			return;

		LastEnemy = Enemy;

		DKPC->AddScore(Enemy->GetActorLocation(), Enemy->GetScoreForJumping());
		//MasterLevel->AddBonusScore(Enemy->GetScoreForJumping());
	}
}

void ADonkeyKongCharacter::Capsule_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADKEnemy* Enemy = Cast<ADKEnemy>(OtherActor))
	{
		GameMode->PlayerDied(this);
	}
}