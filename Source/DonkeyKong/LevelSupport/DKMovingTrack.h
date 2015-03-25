// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKMovingTrack.generated.h"
/*
	Base class for Moving Track volume.

	When player character enters this volume, it will modify character movement
*/
UCLASS()
class DONKEYKONG_API ADKMovingTrack : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* TrackVolume;

protected:
	/* Direction of modifier in Y direction. Use either negative or positive number. */
	UPROPERTY(EditAnywhere, Category = "Config")
		float Direction;
	/* Magnitude of modifier, how much movement speed will be modified in this direction. */
	UPROPERTY(EditAnywhere, Category = "Config")
		float Magnitude;

	UPROPERTY(BlueprintReadOnly)
		TArray<class ADonkeyKongCharacter*> AffectedCharacters;

public:
	// Sets default values for this actor's properties
	ADKMovingTrack();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
protected:
	UFUNCTION()
		void TrackVolume_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TrackVolume_EndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
