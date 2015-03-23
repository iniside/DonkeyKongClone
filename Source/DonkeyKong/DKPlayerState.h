// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DKGlobalTypes.h"
#include "GameFramework/PlayerState.h"
#include "DKPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_API ADKPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Info")
		int32 CurrentLifes;

	UPROPERTY(BlueprintReadOnly, Category = "Player Info")
		int32 CurrentScore;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Info")
		FName CurrentLevel;
public:
	ADKPlayerState(const FObjectInitializer& ObjectInitializer);
	
	/* Adds score to current player. */
	inline void AddScore(int32 ScoreIn) { CurrentScore += ScoreIn; };
	
	/* Remove single life from current player. */
	inline void RemoveOneLife() { CurrentLifes -= 1; };
	
	/* Sets level in which player currently is. */
	inline void SetCurrentLevel(const FName& LevelName) { CurrentLevel = LevelName; };
	
	/* Get current lifes of this player. */
	inline int32 GetCurrentLifes() { return CurrentLifes; };

	/* Loads PlayerState properties from Save file. */
	void LoadStateFromSave(const FDKCharacterData& DataIn);

	/* Gets current character data from PlayerState properties. */
	FDKCharacterData GetCurrentCharacterData();
};
