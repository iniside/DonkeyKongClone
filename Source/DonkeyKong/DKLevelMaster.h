// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKLevelMaster.generated.h"
/*
	Master actor to controll level specific behaviors.
*/
UCLASS()
class DONKEYKONG_API ADKLevelMaster : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneRoot;

	/*
		Component used to determine if player reached end of level.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* EndLevelTrigger;

public:	
	// Sets default values for this actor's properties
	ADKLevelMaster();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		FName NextLevelName;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"), Category = "Config")
		FVector EndLevelTriggetLocation;

protected:
	UFUNCTION()
		void EndLevelTrigger_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	/*
		Called when player reaches end of current level.
	*/
	void EndLevel();

	UFUNCTION(BlueprintImplementableEvent, Category = "Level")
		void OnEndLevel();
};
