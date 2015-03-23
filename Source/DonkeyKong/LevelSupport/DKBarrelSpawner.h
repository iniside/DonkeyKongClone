// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "DKBarrelSpawner.generated.h"

UCLASS()
class DONKEYKONG_API ADKBarrelSpawner : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Triggers")
	class USceneComponent* SceneRoot;

	/* Kills Barrels, that touch this volume. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Triggers")
	class UBoxComponent* KillBarrelVolume;

	/* AActor Overrides - END **/
protected:
	/* Class of barrel to spawn. */
	UPROPERTY(EditAnywhere, Category = "Barrel")
		TSubclassOf<class ADKBarrel> BarrelClass;

	/* Where to spawn new barrel. */
	UPROPERTY(EditAnywhere, meta=(MakeEditWidget = "true"), Category = "Config")
		FVector SpawnLocation;

	/*
		Minimum time that must pass for new barrel to be spawned.
		Spawn time is randomly selected between MinimumSpawnTime and MaximumSpawnTime.
	*/
	UPROPERTY(EditAnywhere, Category = "Config")
		float MinimumSpawnTime;

	/* Maximum time time, in which barrel must be spawned. */
	UPROPERTY(EditAnywhere, Category = "Config")
		float MaximumSpawnTime;

	/* Sets location of KillBarrelVolume */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget = "true"), Category = "Config")
		FVector KillBarrelVolumeLocation;
private:
	FTimerHandle BarrelSpawnedTimerHandle;

public:
	// Sets default values for this actor's properties
	ADKBarrelSpawner();
	/** AActor Overrides - BEGIN */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Reset() override;

protected:
	UFUNCTION()
		void SpawnNewBarrel();
	/* Called when barrel will overlap KillBareelVolume */
	UFUNCTION()
		void KillBarrelVolume_OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
