// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKBarrelSpawner.generated.h"

UCLASS()
class DONKEYKONG_API ADKBarrelSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADKBarrelSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	/*
		Class of barrel to spawn.
	*/
	UPROPERTY(EditAnywhere, Category = "Barrel")
		TSubclassOf<class ADKBarrel> BarrelClass;
	/*
		Where to spawn new barrel.
	*/
	UPROPERTY(EditAnywhere, meta=(MakeEditWidget = "true"), Category = "Config")
		FVector SpawnLocation;
	/*
		Minimum time that must pass for new barrel to be spawned.

		Spawn time is randomly selected between MinimumSpawnTime and MaximumSpawnTime.
	*/
	UPROPERTY(EditAnywhere, Category = "Config")
		float MinimumSpawnTime;
	/*
		Maximum time time, in which barrel must be spawned.
	*/
	UPROPERTY(EditAnywhere, Category = "Config")
		float MaximumSpawnTime;

private:
	FTimerHandle BarrelSpawnedTimerHandle;

protected:
	UFUNCTION()
		void SpawnNewBarrel();
};
