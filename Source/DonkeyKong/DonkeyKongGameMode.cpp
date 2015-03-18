// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong.h"
#include "DKLevelMaster.h"
#include "DonkeyKongGameMode.h"
#include "DKGameInstance.h"
#include "DKPlayerController.h"
#include "DKBarrel.h"
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

	GameInstance = Cast<UDKGameInstance>(GetGameInstance());

	FTimerDelegate del = FTimerDelegate::CreateUObject(this, &ADonkeyKongGameMode::SubtractScore);

	GetWorldTimerManager().SetTimer(ScoreSubtractionTimeHandle, del, HowOftenSubtractScore,
		true, HowOftenSubtractScore);
}

void ADonkeyKongGameMode::AddScore(int32 ScoreIn)
{
	BonusLevelScore += ScoreIn;

	GameInstance->AddScore(ScoreIn);
}

void ADonkeyKongGameMode::PlayerDied(class ADonkeyKongCharacter* CharacterIn)
{
	OnPlayerDied(CharacterIn);
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

void ADonkeyKongGameMode::RespawnPlayer(class ADonkeyKongCharacter* CharacterIn, 
			class ADKPlayerController* PCIn)
{
	/*
		Not enough lifes to respawn, probabaly should print something on screen.
	*/
	if (GameInstance->GetPlayerLifes() <= 0)
		return;

	if (!CharacterIn || !PCIn)
		return;

	AActor* PlayerStart = FindPlayerStart(PCIn);
	if (!PlayerStart)
		return;
	GameInstance->SubtractPlayerLife();
	GameInstance->SubtractScore(BonusLevelScore);
	//CharacterIn->TeleportTo(PlayerStart->GetActorLocation(),FRotator(0,0,0));
	RestartGame();
	//reset scores to state before respawns (TODO! Check if this really worked this way!).
	//
	//BonusLevelScore = 0;

	
}

void ADonkeyKongGameMode::Restart()
{
	GameInstance->ResetCurrentGame();
	UGameplayStatics::OpenLevel(this, FirstLevelName);
}