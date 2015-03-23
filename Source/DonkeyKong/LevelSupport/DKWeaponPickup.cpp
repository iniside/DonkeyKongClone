// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "../DKWeapon.h"
#include "../DonkeyKongCharacter.h"
#include "DKWeaponPickup.h"


// Sets default values
ADKWeaponPickup::ADKWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADKWeaponPickup::Collision_BeginOverlap);

	bPickedWeapon = false;
}

// Called when the game starts or when spawned
void ADKWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKWeaponPickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
void ADKWeaponPickup::Reset()
{
	bPickedWeapon = false;
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}
void ADKWeaponPickup::Collision_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if player already picked weapon, just return, we can't give weapon only once.
	if (bPickedWeapon)
		return;

	if (ADonkeyKongCharacter* MyChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoCollisionFail = true;

		ADKWeapon* tempWeapon = GetWorld()->SpawnActor<ADKWeapon>(WeaponPick, SpawnParams);

		MyChar->EquipWeapon(tempWeapon);

		bPickedWeapon = true;
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
	}
}