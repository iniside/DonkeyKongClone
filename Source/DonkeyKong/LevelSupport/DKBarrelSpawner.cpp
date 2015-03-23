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
	float SpawnTime = FMath::FRandRange(MinimumSpawnTime, MaximumSpawnTime);
	FTimerDelegate del = FTimerDelegate::CreateUObject(this, &ADKBarrelSpawner::SpawnNewBarrel);
	GetWorldTimerManager().SetTimer(BarrelSpawnedTimerHandle, del, SpawnTime, true, SpawnTime);
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

void ADKBarrelSpawner::Reset()
{
	Super::Reset();

	//GetWorldTimerManager().ClearTimer(BarrelSpawnedTimerHandle);
	for (auto It = TActorIterator<ADKBarrel>(GetWorld()); It; ++It)
	{
		It->Destroy();
	}
}

void ADKBarrelSpawner::SpawnNewBarrel()
{
	//spawn barrel.

	if (BarrelClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoCollisionFail = true;
		//because SpawnLocation value is relative to this actor location.
		FVector SpawnLoc = SpawnLocation + GetActorLocation();
		GetWorld()->SpawnActor<ADKBarrel>(BarrelClass, SpawnLoc, FRotator(0, 0, 0),
			SpawnParams);
	}

	GetWorldTimerManager().ClearTimer(BarrelSpawnedTimerHandle);

	float SpawnTime = FMath::FRandRange(MinimumSpawnTime, MaximumSpawnTime);
	FTimerDelegate del = FTimerDelegate::CreateUObject(this, &ADKBarrelSpawner::SpawnNewBarrel);
	GetWorldTimerManager().SetTimer(BarrelSpawnedTimerHandle, del, SpawnTime, true, SpawnTime);
}

void ADKBarrelSpawner::KillBarrelVolume_OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADKBarrel* Barrel = Cast<ADKBarrel>(OtherActor))
	{
		Barrel->Destroy();
	}
}