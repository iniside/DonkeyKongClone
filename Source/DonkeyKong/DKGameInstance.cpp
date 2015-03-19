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
}

void UDKGameInstance::AddScore(int32 PlayerIndex, int32 ScoreIn)
{
	TotalGameScore[PlayerIndex] += ScoreIn;
}

void UDKGameInstance::SubtractScore(int32 PlayerIndex, int32 ScoreIn)
{
	TotalGameScore[PlayerIndex] -= ScoreIn;
}

void UDKGameInstance::SubtractPlayerLife(int32 PlayerIndex)
{
	PlayerLifes[PlayerIndex] -= 1;
}

void UDKGameInstance::ResetCurrentGame()
{
	PlayerLifes = StartingLifes;
	int32 scoreNum = TotalGameScore.Num();
	for (int32 Index = 0; Index < scoreNum; Index++)
	{
		TotalGameScore[Index] = 0;
	}
	//TotalGameScore = 0;
}