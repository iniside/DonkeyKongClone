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
	BaseLevelScore.Add(5000);//player 1
	BaseLevelScore.Add(5000);//player 2
	BonusLevelScore.Add(0);//player 1
	BonusLevelScore.Add(0);//player 2
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

void ADonkeyKongGameMode::AddScore(int32 PlayerIndex, int32 ScoreIn)
{
	BonusLevelScore[PlayerIndex] += ScoreIn;

	GameInstance->AddScore(PlayerIndex, ScoreIn);
}

void ADonkeyKongGameMode::PlayerDied(class ADonkeyKongCharacter* CharacterIn)
{
	OnPlayerDied(CharacterIn);
}

void ADonkeyKongGameMode::SubtractScore()
{
	//PlayerIndex = NumPlayers - 1;
	for (int32 Player = 0; Player < NumPlayers; Player++)
	{
		BaseLevelScore[Player] = BaseLevelScore[Player] - SubtractionAmount;
		if (BaseLevelScore[Player] <= 0)
		{
			GetWorldTimerManager().ClearTimer(ScoreSubtractionTimeHandle);
			BaseLevelScore[Player] = 0;
		}
	}
	//BaseLevelScore[0] = BaseLevelScore[0] - SubtractionAmount;
	//BaseLevelScore[1] = BaseLevelScore[1] - SubtractionAmount;
	//if (BaseLevelScore[0] <= 0)
	//{
	//	GetWorldTimerManager().ClearTimer(ScoreSubtractionTimeHandle);
	//	BaseLevelScore[0] = 0;
	//	BaseLevelScore[1] = 0;
	//}
}

void ADonkeyKongGameMode::RespawnPlayer(class ADonkeyKongCharacter* CharacterIn, 
			class ADKPlayerController* PCIn)
{
	/*
		Not enough lifes to respawn, probabaly should print something on screen.
	*/
	if (!CharacterIn || !PCIn)
		return;
	
	int32 PlayerIndex = PCIn->NetPlayerIndex;
	
	if (GameInstance->GetPlayerLifes(PlayerIndex) <= 0)
		return;

	AActor* PlayerStart = FindPlayerStart(PCIn);
	if (!PlayerStart)
		return;
	
	GameInstance->SubtractPlayerLife(PlayerIndex);
	GameInstance->SubtractScore(PlayerIndex, BonusLevelScore[PlayerIndex]);
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

void ADonkeyKongGameMode::StartOnePlayer()
{

}
void ADonkeyKongGameMode::StartTwoPlayers()
{

}