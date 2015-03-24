// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKEnemySpawner.generated.h"
/*
	Base class fot spawning enemies in level.
*/
UCLASS()
class DONKEYKONG_API ADKEnemySpawner : public AActor
{
	GENERATED_BODY()
protected:
	/* Class of enemy to spawn. */
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<class ADKEnemy> EnemyClass;

	/* Location at which enemy will be spawned. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget= "true"), Category = "Config")
		FVector SpawnLocation;
	
	/* Maximum number of enemies that can be spawned, during single level. < 0, infinite spawn.*/
	UPROPERTY(EditAnywhere, Category = "Config")
		int32 NumberOfEnemies;

	/* Minimum time interval at which enemy will be spawned. */
	UPROPERTY(EditAnywhere, Category = "Config")
		float MinSpawnInterval;

	/* Maximum time interval at which enemy will be spawned. */
	UPROPERTY(EditAnywhere, Category = "Config")
		float MaxSpawnInterval;

	/* Enemies which this spawner, spawned and owns. */
	UPROPERTY()
		TArray<class ADKEnemy*> OwnedEnemies;
private:
	FTimerHandle EnemySpawnTimerHandle;
	int32 CurrentSpawnedEnemies;
public:	
	// Sets default values for this actor's properties
	ADKEnemySpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void Reset() override;

protected:
	UFUNCTION()
		void SpawnEnemy();
	
};
