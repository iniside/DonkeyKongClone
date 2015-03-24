// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "../Enemies/DKEnemy.h"
#include "DKEnemySpawner.h"


// Sets default values
ADKEnemySpawner::ADKEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentSpawnedEnemies = 0;

	MinSpawnInterval = 1.3;
	MaxSpawnInterval = 2.5;
}

// Called when the game starts or when spawned
void ADKEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	float SpawnTime = FMath::FRandRange(MinSpawnInterval, MaxSpawnInterval);

	FTimerDelegate del = FTimerDelegate::CreateUObject(this, &ADKEnemySpawner::SpawnEnemy);
	GetWorldTimerManager().SetTimer(EnemySpawnTimerHandle, del, SpawnTime, true);
}

// Called every frame
void ADKEnemySpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADKEnemySpawner::Reset()
{
	for (ADKEnemy* enemy : OwnedEnemies)
	{
		enemy->Destroy();
	}
	CurrentSpawnedEnemies = 0;
	OwnedEnemies.Empty();
	GetWorldTimerManager().ClearTimer(EnemySpawnTimerHandle);

	float SpawnTime = FMath::FRandRange(MinSpawnInterval, MaxSpawnInterval);

	FTimerDelegate del = FTimerDelegate::CreateUObject(this, &ADKEnemySpawner::SpawnEnemy);
	GetWorldTimerManager().SetTimer(EnemySpawnTimerHandle, del, SpawnTime, true);
}

void ADKEnemySpawner::SpawnEnemy()
{
	if (NumberOfEnemies > CurrentSpawnedEnemies
		|| NumberOfEnemies < 0)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoCollisionFail = true;
		FVector RealLocation = GetActorLocation() + SpawnLocation;
		ADKEnemy* enemy = GetWorld()->SpawnActor<ADKEnemy>(EnemyClass, RealLocation,
			FRotator(0, 0, 0), SpawnParams);
		
		OwnedEnemies.Add(enemy);
		CurrentSpawnedEnemies++;

		//pick random time for next spawn.
		GetWorldTimerManager().ClearTimer(EnemySpawnTimerHandle);

		float SpawnTime = FMath::FRandRange(MinSpawnInterval, MaxSpawnInterval);

		FTimerDelegate del = FTimerDelegate::CreateUObject(this, &ADKEnemySpawner::SpawnEnemy);
		GetWorldTimerManager().SetTimer(EnemySpawnTimerHandle, del, SpawnTime, true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(EnemySpawnTimerHandle);
	}
}