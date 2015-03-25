// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKBlueprintFunctionLibrary.h"
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
	FDKCharacterData PlayerStartData(StartingLifes, 0, StartingLevel);
	UDKBlueprintFunctionLibrary::SavePlayerOne(PlayerStartData);
	if (PlayerNumber > 1)
	{
		UDKBlueprintFunctionLibrary::SavePlayerTwo(PlayerStartData);
	}
}

void UDKGameInstance::SwapPlayers()
{
	if (PlayerNumber > 1)
	{
		if (CurrentPlayerIndex == 0)
			CurrentPlayerIndex = 1;
		else
			CurrentPlayerIndex = 0;
	}
}