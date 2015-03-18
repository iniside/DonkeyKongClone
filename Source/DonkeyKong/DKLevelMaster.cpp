// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKLevelMaster.h"


// Sets default values
ADKLevelMaster::ADKLevelMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void ADKLevelMaster::BeginPlay()
{
	Super::BeginPlay();
	
	//safer
	FTimerDelegate del = FTimerDelegate::CreateUObject(this, &ADKLevelMaster::SubtractScore);

	GetWorldTimerManager().SetTimer(ScoreSubtractionTimeHandle, del, HowOftenSubtractScore,
		true, HowOftenSubtractScore);
}

// Called every frame
void ADKLevelMaster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADKLevelMaster::SubtractScore()
{
	StartingScore = StartingScore - SubtractionAmount;
	if (StartingScore <= 0)
	{
		GetWorldTimerManager().ClearTimer(ScoreSubtractionTimeHandle);
		StartingScore = 0;
	}
}

void ADKLevelMaster::AddBonusScore(int32 ScoreIn)
{
	LevelBonusScore += ScoreIn;
}