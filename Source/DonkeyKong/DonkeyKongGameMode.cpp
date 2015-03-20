// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong.h"
#include "DonkeyKongGameMode.h"
#include "DKGameInstance.h"
#include "DKPlayerController.h"

#include "Enemies/DKBarrel.h"
#include "LevelSupport/DKLevelMaster.h"
#include "LevelSupport/DKBarrelSpawner.h"
#include "DonkeyKongCharacter.h"

ADonkeyKongGameMode::ADonkeyKongGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerNumber = 1;

	BaseLevelScore = 5000;
	HowOftenSubtractScore = 1.55;
	SubtractionAmount = 100;
}

void ADonkeyKongGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (auto It = TActorIterator<ADKLevelMaster>(GetWorld()); It; ++It)
	{
		MasterLevel = *It;
		break;
	}

	GameInstance = Cast<UDKGameInstance>(GetGameInstance());

	FTimerDelegate del = FTimerDelegate::CreateUObject(this, &ADonkeyKongGameMode::SubtractScore);
	GetWorldTimerManager().SetTimer(ScoreSubtractionTimeHandle, del, HowOftenSubtractScore,
		true, HowOftenSubtractScore);
}

void ADonkeyKongGameMode::PlayerDied(class ADonkeyKongCharacter* CharacterIn)
{
	OnPlayerDied(CharacterIn);
	OnPlayerDeath.Broadcast();
}

void ADonkeyKongGameMode::Restart()
{
	GameInstance->ResetCurrentGame();
	UGameplayStatics::OpenLevel(this, FirstLevelName);
}

void ADonkeyKongGameMode::GameOver()
{
	for (auto It = TActorIterator<ADKBarrelSpawner>(GetWorld()); It; ++It)
	{
		It->Reset();
	}
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