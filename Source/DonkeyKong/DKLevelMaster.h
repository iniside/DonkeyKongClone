// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKLevelMaster.generated.h"

UCLASS()
class DONKEYKONG_API ADKLevelMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADKLevelMaster();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	/*
		Total score accumulated between levels
		At the and of each level remaining of StartingScore is added.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Score")
		int32 TotalScore;
	/*
		Base score we have when level start. It's subtracted
		when player is on level, until level is beaten.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Score")
		int32 StartingScore;
	/*
		Current bonus score, from avoiding barrels, killing enemies etc.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Score")
		int32 LevelBonusScore;
	
	/*
		Time in seconds, between score subtraction.
	*/
	UPROPERTY(EditAnywhere, Category = "Config")
		float HowOftenSubtractScore;

	/*
		How much score will be subtracted on each period.
	*/
	UPROPERTY(EditAnywhere, Category = "Score")
		int32 SubtractionAmount;
private:
	FTimerHandle ScoreSubtractionTimeHandle;


protected:
	UFUNCTION()
	void SubtractScore();
};
