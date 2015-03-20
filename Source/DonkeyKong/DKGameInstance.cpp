// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKGameInstance.h"

UDKGameInstance::UDKGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StartingLifes.Add(3); //player 1
	StartingLifes.Add(3); //player 2
	PlayerLifes = StartingLifes;

	TotalGameScore.Add(0); //player 1
	TotalGameScore.Add(0); //player 2

	CurrentPlayerIndex = 0;

	PlayerNumber = 1;
}

void UDKGameInstance::AddScore(int32 PlayerIndex, int32 ScoreIn)
{
	TotalGameScore[CurrentPlayerIndex] += ScoreIn;
}

void UDKGameInstance::SubtractPlayerLife(int32 PlayerIndex)
{
	if (PlayerNumber <= 1)
	{
		int32 PlayerLifesNum = PlayerLifes.Num();
		for (int32 Index = 0; Index < PlayerLifesNum; Index++)
		{
			PlayerLifes[Index] -= 1;
		}
	}
	else
	{
		PlayerLifes[CurrentPlayerIndex] -= 1;
	}
	//bit hacky FIX IT!
	//number of players
	//int32 PlayerLifesNum = PlayerLifes.Num();

	//int32 NumOfPlayersWithZeroLifes = 0;
	////check how many player have zero lifes.
	//for (int32 Index = 0; Index < PlayerLifesNum; Index++)
	//{
	//	if (PlayerLifes[Index] == 0)
	//	{
	//		NumOfPlayersWithZeroLifes++;
	//	}
	//}
	////If there are no players with lifes left
	////broadcast event, and handle it, by displaying UI or something.
	//if (NumOfPlayersWithZeroLifes == PlayerLifesNum)
	//{
	//	OnBothPlayersZeroLifes.Broadcast();
	//	return false;
	//}
	//return true;
}

void UDKGameInstance::ResetCurrentGame()
{
	PlayerLifes = StartingLifes;
	int32 scoreNum = TotalGameScore.Num();
	for (int32 Index = 0; Index < scoreNum; Index++)
	{
		TotalGameScore[Index] = 0;
	}
}

void UDKGameInstance::StartOnePlayer()
{
	PlayerNumber = 1;
}
void UDKGameInstance::StartTwoPlayers()
{
	PlayerNumber = 2;
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