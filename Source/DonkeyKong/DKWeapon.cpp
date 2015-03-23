// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DonkeyKongCharacter.h"

#include "Enemies/DKEnemy.h"

#include "DrawDebugHelpers.h"

#include "DKWeapon.h"


// Sets default values
ADKWeapon::ADKWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ADKWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	for (auto Iter = EnemyCollisionType.CreateConstIterator(); Iter; ++Iter)
	{
		const ECollisionChannel & Channel = (*Iter);
		if (FCollisionObjectQueryParams::IsValidObjectQuery(Channel))
		{
			EnemiesTypes.AddObjectTypesToQuery(Channel);
		}
	}
}

// Called every frame
void ADKWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ADKWeapon::ActivateWeapon(class ADonkeyKongCharacter* OwnerIn)
{
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DKOwner = OwnerIn;
	FTimerDelegate del = FTimerDelegate::CreateUObject(this, &ADKWeapon::AutoAttack);
	GetWorldTimerManager().SetTimer(AttackIntervalTimerHandle, del, AttackInterval, true, 0);
}

void ADKWeapon::AutoAttack()
{
	FOverlapResult overlaps;
	FVector CurrentLocation = GetActorLocation();
	FVector EndLocation = CurrentLocation + FVector(0, Range, 0) * DKOwner->GetActorRotation().Vector();
	FCollisionQueryParams Params;
	GetWorld()->OverlapSingle(overlaps, EndLocation, FQuat(),
		FCollisionShape::MakeSphere(CapsuleRadius), Params, EnemiesTypes);

	DrawDebugSphere(GetWorld(), EndLocation, CapsuleRadius, 16, FColor::Red, true, .5);
	//DrawDebugCapsule(GetWorld(), EndLocation, CapsuleHalfHeight, CapsuleRadius, FQuat(),
	//	FColor::Red, true, GetWorld()->TimeSeconds);

	if (overlaps.Actor.IsValid())
	{
		if (ADKEnemy* Enemy = Cast<ADKEnemy>(overlaps.Actor.Get()))
		{
			Enemy->Kill(DKOwner->GetDKPC());
			CurrentKilledEnemies++;
		}
	}

	if (CurrentKilledEnemies > MaximumKilledEnemies)
	{
		StopWeapon();
	}
}

void ADKWeapon::StopWeapon()
{
	GetWorldTimerManager().ClearTimer(AttackIntervalTimerHandle);

	DKOwner->UnEquipWeapon();
}