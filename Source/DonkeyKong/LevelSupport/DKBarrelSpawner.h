// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DKEnemySpawner.h"
#include "GameFramework/Actor.h"
#include "DKBarrelSpawner.generated.h"

UCLASS()
class DONKEYKONG_API ADKBarrelSpawner : public ADKEnemySpawner
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

	/* Sets location of KillBarrelVolume */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget = "true"), Category = "Config")
		FVector KillBarrelVolumeLocation;
public:
	// Sets default values for this actor's properties
	ADKBarrelSpawner();
	/** AActor Overrides - BEGIN */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	UFUNCTION()
		void KillBarrelVolume_OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
