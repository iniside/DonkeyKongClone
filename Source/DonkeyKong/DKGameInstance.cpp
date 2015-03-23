// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKGameInstance.h"

UDKGameInstance::UDKGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentPlayerIndex = 0;
	PlayerNumber = 1;
	bStartTwoPlayers = false;
}

void UDKGameInstance::Init()
{
	Super::Init();
	//used only for debugging, remove before release packagage.
	if (bStartTwoPlayers)
	{
		StartTwoPlayers();
	}
	else
	{
		StartOnePlayer();
	}

}

void UDKGameInstance::AddScore(int32 ScoreIn)
{
	TotalGameScore[CurrentPlayerIndex] += ScoreIn;
}

void UDKGameInstance::SubtractPlayerLife()
{
	PlayerLifes[CurrentPlayerIndex] -= 1;
}

void UDKGameInstance::ResetCurrentGame()
{
	//PlayerLifes = StartingLifes;
	int32 scoreNum = TotalGameScore.Num();
	for (int32 Index = 0; Index < scoreNum; Index++)
	{
		TotalGameScore[Index] = 0;
	}
}

void UDKGameInstance::StartOnePlayer()
{
	PlayerNumber = 1;
	CreateGame();
}
void UDKGameInstance::StartTwoPlayers()
{
	PlayerNumber = 2;
	CreateGame();
}

void UDKGameInstance::CreateGame()
{
	PlayerLifes.Empty();
	CurrentLevel.Empty();
	TotalGameScore.Empty();
	for (int32 Index = 0; Index < PlayerNumber; Index++)
	{
		PlayerLifes.Add(StartingLifes);
		CurrentLevel.Add(StartingLevel);
		TotalGameScore.Add(0);
	}
}

bool UDKGameInstance::AreAnyLifesRemaining()
{
	int32 PlayerLifesNum = PlayerLifes.Num();

	int32 NumOfPlayersWithZeroLifes = 0;
	//check how many player have zero lifes.
	for (int32 Index = 0; Index < PlayerLifesNum; Index++)
	{
		if (PlayerLifes[Index] == 0)
		{
			NumOfPlayersWithZeroLifes++;
		}
	}
	//If there are no players with lifes left
	//broadcast event, and handle it, by displaying UI or something.
	if (NumOfPlayersWithZeroLifes == PlayerLifesNum)
	{
		OnBothPlayersZeroLifes.Broadcast();
		return false;
	}
	return true;
}

