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
		Volume which should encompass ladder.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder Volume", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LadderVolume;
	/*
		Should be placed on surface next to ladder end. (like infront of ladder on roof).	
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder Volume", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LadderEnd;
	/*
		Should be placed on surface next to ladder Begin. (like infront of ladder on floor).
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder Volume", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LadderBegin;
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


	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"), Category = "Ladder")
		FVector BeginLocation;
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"), Category = "Ladder")
		FVector EndLocation;
protected:
	UFUNCTION()
		void LadderEnd_OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void LadderBegin_OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
