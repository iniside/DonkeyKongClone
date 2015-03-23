// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKLevelMaster.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDKOnCharacterRespawned, class ADKPlayerController*);
/*
	Master actor to controll level specific behaviors.
*/
UCLASS()
class DONKEYKONG_API ADKLevelMaster : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneRoot;

	/*
		Component used to determine if player reached end of level.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* EndLevelTrigger;

protected:
	/* Name of next level, player will travel to */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		FName NextLevelName;
	/* Location of trigger, which will finish current level. */
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"), Category = "Config")
		FVector EndLevelTriggetLocation;

	/* Camera actor located in level, to use. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		ACameraActor* Camera;
public:
	FDKOnCharacterRespawned OnCharacterRespawned;

public:
	// Sets default values for this actor's properties
	ADKLevelMaster();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;
protected:
	UFUNCTION()
		void EndLevelTrigger_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void CharacterRespawned(class ADKPlayerController* PCIn);

public:
	/* Called when player reaches end of current level. */
	void EndLevel();

	UFUNCTION(BlueprintImplementableEvent, Category = "Level")
		void OnEndLevel();
};
