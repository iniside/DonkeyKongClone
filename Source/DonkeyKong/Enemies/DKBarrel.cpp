// Fill out your copyright notice in the Description page of Project Settings.

#include "../DonkeyKong.h"
#include "../LevelSupport/DKLadder.h"
#include "../DKPlayerController.h"
#include "DKBarrel.h"


// Sets default values
ADKBarrel::ADKBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	RotMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotMovement"));
	
	bMoveDirection = true;
	bChangeDirection = true;
	bMovingOnLadder = false;

	Move = 400;
	TraceStartDistance = 40;
	RotationRate = FRotator(0, 0, -180);
	Falling = -300;
}

// Called when the game starts or when spawned
void ADKBarrel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADKBarrel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (RotMovement)
		RotMovement->RotationRate = RotationRate;
	FVector DeltaMovement = FVector::ZeroVector;
	
	FHitResult hit;
	if (GetFloor(hit) && !bMovingOnLadder)
	{
		if (bMoveDirection)
		{
			DeltaMovement.Y = FMath::Abs<float>(Move) * -1;// FVector(0, -400, 0);
			TraceStartDistance = FMath::Abs<float>(40);
			RotationRate = FRotator(0, 0, -180);
		}
		else
		{
			DeltaMovement.Y = FMath::Abs<float>(Move);// FVector(0, 400, 0);;
			TraceStartDistance = FMath::Abs<float>(40) * -1;;
			RotationRate = FRotator(0, 0, 180);
		}
		bChangeDirection = true;

		FVector CurrentLocation = GetActorLocation();
		float DesiredLocationZ = hit.Location.Z + 40;
		CurrentLocation.Z = DesiredLocationZ;
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), CurrentLocation, DeltaTime, 5));
	}
	else
	{
		DeltaMovement = FVector(0, 0, Falling);
		if (bChangeDirection)
		{
			if (bMoveDirection)
			{
				bMoveDirection = false;
			}
			else
			{
				bMoveDirection = true;
			}
		}
		bChangeDirection = false;
	}
	DeltaMovement = DeltaMovement * DeltaTime;
	AddActorWorldOffset(DeltaMovement);
}

bool ADKBarrel::GetFloor(FHitResult& out)
{
	FHitResult outResults;
	FVector StartLocation = GetActorLocation() + FVector(0, TraceStartDistance,0);
	FVector EndLocation = StartLocation + (FVector(0, 0, -1) * 100);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FCollisionObjectQueryParams objParams;
	bool hit = GetWorld()->LineTraceSingle(outResults, StartLocation, EndLocation, Params, objParams);

	out = outResults;

	return hit;
}

void ADKBarrel::ClimbDown()
{
	bMovingOnLadder = true;
}

void ADKBarrel::ClimbStop()
{
	bMovingOnLadder = false;
}
void ADKBarrel::Kill(class ADKPlayerController* WhoKilled)
{
	WhoKilled->AddScore(GetActorLocation(), ScoreForKilling);
	Destroy();
}