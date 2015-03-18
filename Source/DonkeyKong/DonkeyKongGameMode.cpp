// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong.h"
#include "DKLevelMaster.h"
#include "DonkeyKongGameMode.h"
#include "DonkeyKongCharacter.h"

ADonkeyKongGameMode::ADonkeyKongGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScroller/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	BaseLevelScore = 5000;
}

void ADonkeyKongGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (auto It = TActorIterator<ADKLevelMaster>(GetWorld()); It; ++It)
	{
		MasterLevel = *It;
		break;
	}

	FTimerDelegate del = FTimerDelegate::CreateUObject(this, &ADonkeyKongGameMode::SubtractScore);

	GetWorldTimerManager().SetTimer(ScoreSubtractionTimeHandle, del, HowOftenSubtractScore,
		true, HowOftenSubtractScore);
}

void ADonkeyKongGameMode::AddScore(int32 ScoreIn)
{
	BonusLevelScore += ScoreIn;
}

void ADonkeyKongGameMode::SubtractScore()
{
	BaseLevelScore = BaseLevelScore - SubtractionAmount;
	if (BaseLevelScore <= 0)
	{
		GetWorldTimerManager().ClearTimer(ScoreSubtractionTimeHandle);
		BaseLevelScore = 0;
	}
}