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

	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static void LoadScoreFromLadder();

	/* Gets full ladderboard from save. */
	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static TArray<FDKScoreLadder> LoadFullLadderBoard();

	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static void SavePlayerOne(const FDKCharacterData& DataIn);

	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static FDKCharacterData LoadPlayerOne();

	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static void SavePlayerTwo(const FDKCharacterData& DataIn);

	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static FDKCharacterData LoadPlayerTwo();

	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Save Game")
		static FDKCharacterData LoadPlayerByIndex(int32 PlayerIndex);
};
