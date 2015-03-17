// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKLadder.generated.h"

UCLASS()
class DONKEYKONG_API ADKLadder : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder Volume", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SceneRoot;
	
	/*
		Where ladder begin. When button is pressed, trace against this volume, to check
		if character can climb on ladder.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder Volume", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LadderBegin;
	/*
		Where ladder begin. When button is pressed, trace against this volume, to check
		if character can climb on ladder.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder Volume", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LadderEnd;
	/*
		While on ladder check for this, to see if we are safe to leave ladder.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder Volume", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LadderBeginDrop;
	/*
		While on ladder check for this, to see if we are safe to leave ladder.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder Volume", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LadderEndDrop;

public:	
	// Sets default values for this actor's properties
	ADKLadder();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Config")
		int32 LadderSections;

	UPROPERTY(EditAnywhere, Category = "Config")
		int32 LadderSteps;

	UPROPERTY(EditAnywhere, Category = "Config")
		FVector LadderVolumeExtens;
	/*
		When we finish climing, where character should be dropped ?
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget = "true"), Category = "Config")
		FVector DropLocationEnd;

	/*
		Location of begin volume.
	*/
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"), Category = "Config")
		FVector LadderBeginLocation;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"), Category = "Config")
		FVector LadderEndLocation;


	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"), Category = "Config")
		FVector LadderBeginDropLocation;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"), Category = "Config")
		FVector LadderEndDropLocation;

protected:
	UFUNCTION()
		void LadderBegin_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void LadderEnd_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void LadderEnd_LadderBeginDrop(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void LadderEnd_LadderEndDrop(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
