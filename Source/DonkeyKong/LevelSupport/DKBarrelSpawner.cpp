// Fill out your copyright notice in the Description page of Project Settings.

#include "../DonkeyKong.h"
#include "../Enemies/DKBarrel.h"
#include "DKBarrelSpawner.h"


// Sets default values
ADKBarrelSpawner::ADKBarrelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	KillBarrelVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("KillBarrelVolume"));
	KillBarrelVolume->AttachTo(RootComponent);


	KillBarrelVolume->OnComponentBeginOverlap.AddDynamic(this, &ADKBarrelSpawner::KillBarrelVolume_OnBeginOverlap);

}

// Called when the game starts or when spawned
void ADKBarrelSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADKBarrelSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
void ADKBarrelSpawner::OnConstruction(const FTransform& Transform)
{
	KillBarrelVolume->SetRelativeLocation(KillBarrelVolumeLocation);
}

void ADKBarrelSpawner::KillBarrelVolume_OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADKBarrel* Barrel = Cast<ADKBarrel>(OtherActor))
	{
		OwnedEnemies.RemoveSingle(Barrel);
		OwnedEnemies.Shrink();
		Barrel->Destroy();
	}
}