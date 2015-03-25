// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKPlayerState.h"


ADKPlayerState::ADKPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentLifes = 3;
	CurrentScore = 0;
}

void ADKPlayerState::LoadStateFromSave(const FDKCharacterData& DataIn)
{
	CurrentLifes = DataIn.CurrentLifes;
	CurrentScore = DataIn.CurrentScore;
	CurrentLevel = DataIn.CurrentLevel;
	bFinishedGame = DataIn.bFinishedGame;
}

FDKCharacterData ADKPlayerState::GetCurrentCharacterData()
{
	FDKCharacterData DataOut(CurrentLifes, CurrentScore, CurrentLevel, bFinishedGame);
	return DataOut;
}