// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKGameInstance.h"

UDKGameInstance::UDKGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StartingLifes = 3;
	PlayerLifes = StartingLifes;
}

void UDKGameInstance::AddScore(int32 ScoreIn)
{
	TotalGameScore += ScoreIn;
}

void UDKGameInstance::SubtractScore(int32 ScoreIn)
{
	TotalGameScore -= ScoreIn;
}

void UDKGameInstance::SubtractPlayerLife()
{
	PlayerLifes -= 1;
}

void UDKGameInstance::ResetCurrentGame()
{
	PlayerLifes = StartingLifes;
	TotalGameScore = 0;
}