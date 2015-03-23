// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"

#include "DKSaveGame.h"
#include "DKPlayerSave.h"

#include "DKBlueprintFunctionLibrary.h"



void UDKBlueprintFunctionLibrary::SaveNewScoreToLadder(const FString& PlayerName, int32 Score)
{
	UDKSaveGame* saveGame = Cast<UDKSaveGame>(UGameplayStatics::LoadGameFromSlot(FSaveSlotNames::LadderBoardSlot.SlotName,
		FSaveSlotNames::LadderBoardSlot.UserIndex));
	if (saveGame)
	{
		FDKScoreLadder newScore(PlayerName, Score);
		saveGame->LadderScore.Add(newScore);
		//sort so highest score will be on top.
		saveGame->LadderScore.Sort();
		//save over existing save file.
		UGameplayStatics::SaveGameToSlot(saveGame, FSaveSlotNames::LadderBoardSlot.SlotName,
			FSaveSlotNames::LadderBoardSlot.UserIndex);
		//we can also implement some kind of limiter to prevent from having to many scores.
		//if (Num() > 10)
		//Sort()
		//RemoveLowest
		//add new
		//Sort();
	}
	else
	{
		UDKSaveGame* newSaveGame = Cast<UDKSaveGame>(UGameplayStatics::CreateSaveGameObject(UDKSaveGame::StaticClass()));
		FDKScoreLadder newScore(PlayerName, Score);
		newSaveGame->LadderScore.Add(newScore);

		UGameplayStatics::SaveGameToSlot(newSaveGame, FSaveSlotNames::LadderBoardSlot.SlotName,
			FSaveSlotNames::LadderBoardSlot.UserIndex);
	}
}
void UDKBlueprintFunctionLibrary::LoadScoreFromLadder()
{

}
TArray<FDKScoreLadder> UDKBlueprintFunctionLibrary::LoadFullLadderBoard()
{
	TArray<FDKScoreLadder> returnVal;

	UDKSaveGame* saveGame = Cast<UDKSaveGame>(UGameplayStatics::LoadGameFromSlot(FSaveSlotNames::LadderBoardSlot.SlotName,
		FSaveSlotNames::LadderBoardSlot.UserIndex));
	
	if (!saveGame)
		return returnVal;
	saveGame->LadderScore.Sort();
	return saveGame->LadderScore;
}

void UDKBlueprintFunctionLibrary::SavePlayerOne(const FDKCharacterData& DataIn)
{
	UDKPlayerSave* saveGame = Cast<UDKPlayerSave>(UGameplayStatics::LoadGameFromSlot(FSaveSlotNames::PlayerOneSlot.SlotName,
		FSaveSlotNames::PlayerOneSlot.UserIndex));
	if (saveGame)
	{
		saveGame->CharacterData = DataIn;

		UGameplayStatics::SaveGameToSlot(saveGame, FSaveSlotNames::PlayerOneSlot.SlotName,
			FSaveSlotNames::PlayerOneSlot.UserIndex);
	}
	else
	{
		UDKPlayerSave* newSaveGame = Cast<UDKPlayerSave>(UGameplayStatics::CreateSaveGameObject(UDKPlayerSave::StaticClass()));
		newSaveGame->CharacterData = DataIn;

		UGameplayStatics::SaveGameToSlot(newSaveGame, FSaveSlotNames::PlayerOneSlot.SlotName,
			FSaveSlotNames::PlayerOneSlot.UserIndex);
	}
}

FDKCharacterData UDKBlueprintFunctionLibrary::LoadPlayerOne()
{
	FDKCharacterData returnData;
	UDKPlayerSave* saveGame = Cast<UDKPlayerSave>(UGameplayStatics::LoadGameFromSlot(FSaveSlotNames::PlayerOneSlot.SlotName,
		FSaveSlotNames::PlayerOneSlot.UserIndex));

	if (!saveGame)
		return returnData;

	return saveGame->CharacterData;
}

void UDKBlueprintFunctionLibrary::SavePlayerTwo(const FDKCharacterData& DataIn)
{
	UDKPlayerSave* saveGame = Cast<UDKPlayerSave>(UGameplayStatics::LoadGameFromSlot(FSaveSlotNames::PlayerTwoSlot.SlotName,
		FSaveSlotNames::PlayerTwoSlot.UserIndex));
	if (saveGame)
	{
		saveGame->CharacterData = DataIn;

		UGameplayStatics::SaveGameToSlot(saveGame, FSaveSlotNames::PlayerTwoSlot.SlotName,
			FSaveSlotNames::PlayerTwoSlot.UserIndex);
	}
	else
	{
		UDKPlayerSave* newSaveGame = Cast<UDKPlayerSave>(UGameplayStatics::CreateSaveGameObject(UDKPlayerSave::StaticClass()));
		newSaveGame->CharacterData = DataIn;

		UGameplayStatics::SaveGameToSlot(newSaveGame, FSaveSlotNames::PlayerTwoSlot.SlotName,
			FSaveSlotNames::PlayerTwoSlot.UserIndex);
	}
}


FDKCharacterData UDKBlueprintFunctionLibrary::LoadPlayerTwo()
{
	FDKCharacterData returnData;
	UDKPlayerSave* saveGame = Cast<UDKPlayerSave>(UGameplayStatics::LoadGameFromSlot(FSaveSlotNames::PlayerTwoSlot.SlotName,
		FSaveSlotNames::PlayerTwoSlot.UserIndex));

	if (!saveGame)
		return returnData;

	return saveGame->CharacterData;
}