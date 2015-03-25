// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DKGlobalTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DKBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_API UDKBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/* Save new score and player to existing ladderboard. */
	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static void SaveNewScoreToLadder(const FString& PlayerName, int32 Score);

	/* Gets full ladderboard from save. */
	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static TArray<FDKScoreLadder> LoadFullLadderBoard();
	
	/* Save player one state to save file. */
	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static void SavePlayerOne(const FDKCharacterData& DataIn);

	/* Load player one state from save file. */
	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static FDKCharacterData LoadPlayerOne();

	/* Save player two state to save file. */
	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static void SavePlayerTwo(const FDKCharacterData& DataIn);

	/* Load player two state from save file. */
	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static FDKCharacterData LoadPlayerTwo();

	/* Load player state from save file by Index. 0 - player one, 1 - player two.*/
	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static FDKCharacterData LoadPlayerByIndex(int32 PlayerIndex);
};
