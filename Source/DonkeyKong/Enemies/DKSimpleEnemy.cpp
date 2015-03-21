// Fill out your copyright notice in the Description page of Project Settings.

#include "../DonkeyKong.h"
#include "../LevelSupport/DKLadder.h"
#include "DKSimpleEnemy.h"


// Sets default values
ADKSimpleEnemy::ADKSimpleEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CurrentMoveDireaction = 1;
	bIsClimbing = false;

	MinSearchDistance = 100;
	MaxSearchDistance = 300;
}

// Called when the game starts or when spawned
void ADKSimpleEnemy::BeginPlay()
{
	Super::BeginPlay();
	for (auto Iter = FloorToTrace.CreateConstIterator(); Iter; ++Iter)
	{
		const ECollisionChannel & Channel = (*Iter);
		if (FCollisionObjectQueryParams::IsValidObjectQuery(Channel))
		{
			FloorColiision.AddObjectTypesToQuery(Channel);
		}
	}

	FHitResult hit;
	FindPointToMove(hit);
	PointToMove = hit.Location;
}

// Called every frame
void ADKSimpleEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector DeltaMovement = FVector::ZeroVector;
	FVector CurrentLocation = GetActorLocation();
	FHitResult hit;

	FBox TargetBox(PointToMove - 40, PointToMove + 40);

	bool ReachedTarget = FMath::PointBoxIntersection(CurrentLocation, TargetBox);

	if (SearchForFloor(hit) && !bIsClimbing
		&& !ReachedTarget)
	{
		DeltaMovement.Y = CurrentMoveDireaction * MovementSpeed;// FVector(0, -400, 0);

		float DesiredLocationZ = hit.Location.Z + 40;
		CurrentLocation.Z = DesiredLocationZ;
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), CurrentLocation, DeltaTime, 5));
	}
	else if (ReachedTarget)
	{
		//reached current target, let's search for new direction.
		FHitResult hit;
		FindPointToMove(hit);
		PointToMove = hit.Location;
	}
	else if (!bIsClimbing)
	{
		//no floor and not moving on ladder, try to find new direction.
		FHitResult hit;
		FindPointToMove(hit);
		PointToMove = hit.Location;
	}
	else if (bIsClimbing)
	{
		DeltaMovement.Z = ClimbingDirection * MovementSpeed;
	}
	DeltaMovement = DeltaMovement * DeltaTime;
	AddActorWorldOffset(DeltaMovement);
}


bool ADKSimpleEnemy::SearchForFloor(FHitResult& HitOut)
{
	//we could pick Right vector, from rotation
	//but I'm not sure it would be really accurate.
	//while movement is only in 2D, actor can still rotate in 3D, which might lead to undesirable results.
	FVector StartTrace = GetActorLocation() + FVector(0, CurrentMoveDireaction, 0) * 100;
	FVector EndTrace = (FVector(0, 0, -1) * 100) + StartTrace;

	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	bool anyHit = GetWorld()->LineTraceSingle(Hit, StartTrace, EndTrace, QueryParams, FloorColiision);
	HitOut = Hit;
	return anyHit;
}

bool ADKSimpleEnemy::FindPointToMove(FHitResult& HitOut)
{
	FVector SearchDirection(0, 1, 0);
	SearchDirection.Y = FMath::RandRange(-1, 1); //randomly pick direction
	while (SearchDirection.Y == 0) //prevent direction from being zero.
	{
		SearchDirection.Y = FMath::RandRange(-1, 1);
	}
	CurrentMoveDireaction = SearchDirection.Y;
	float SearchDistance = FMath::FRandRange(MinSearchDistance, MaxSearchDistance);//randomly pick distance.

	bool SearchResult = false;
	FHitResult Hit;

	FVector StartTrace = GetActorLocation() + SearchDirection*SearchDistance;
	FVector EndTrace = (FVector(0, 0, -1) * 150) + StartTrace;
	//keep searching until we will find valid point.
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	while (!SearchResult)
	{
		SearchResult = GetWorld()->LineTraceSingle(Hit, StartTrace, EndTrace, QueryParams, FloorColiision);
		//we didn't found floor,
		if (!SearchResult)
		{
			//so we just pick random direcion and distance again, and try again.
			SearchDirection.Y = FMath::RandRange(-1, 1); //randomly pick direction
			while (SearchDirection.Y == 0)
			{
				SearchDirection.Y = FMath::RandRange(-1, 1);
			}
			CurrentMoveDireaction = SearchDirection.Y;
			float SearchDistance = FMath::FRandRange(MinSearchDistance, MaxSearchDistance);//randomly pick distance.
			StartTrace = GetActorLocation() + SearchDirection*SearchDistance;
			EndTrace = (FVector(0, 0, -1) * 150) + StartTrace;
		}
	}
	//ok we found floor.
	HitOut = Hit;

	return SearchResult;
}

void ADKSimpleEnemy::ClimbUp()
{
	bIsClimbing = true;
	ClimbingDirection = 1;
}
void ADKSimpleEnemy::ClimbDown()
{
	bIsClimbing = true;
	ClimbingDirection = -1;
}
void ADKSimpleEnemy::ClimbStop()
{
	bIsClimbing = false;
}