// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "DonkeyKongGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDKOnPlayerDeath);

UCLASS(minimalapi)
class ADonkeyKongGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADonkeyKongGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

protected:
	/*
		This level will be opened when player press Restart Button.
	*/
	UPROPERTY(EditAnywhere, Category = "Config")
		FName FirstLevelName;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class ADKLevelMaster* MasterLevel;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class UDKGameInstance* GameInstance;

	/* Base score for level, it's subtracted over time. */
	UPROPERTY(BlueprintReadOnly, Category = "Score")
		int32 BaseLevelScore;

	/* Time in seconds, between score subtraction. */
	UPROPERTY(EditAnywhere, Category = "Config")
		float HowOftenSubtractScore;

	/* How much score will be subtracted on each period. */
	UPROPERTY(EditAnywhere, Category = "Score")
		int32 SubtractionAmount;

private:
	FTimerHandle ScoreSubtractionTimeHandle;
public:
	/* Number of players in current game. EditAnywhere, for editor debug. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 PlayerNumber;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Donkey Kong|Game Mode")
		FDKOnPlayerDeath OnPlayerDeath;
public:

	/* Called when played die. */
	void PlayerDied(class ADonkeyKongCharacter* CharacterIn);
	
	/* Called when played die. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Donkey Kong | Player")
		void OnPlayerDied(class ADonkeyKongCharacter* CharacterIn);
	
	/* Restart game and move to first level */
	UFUNCTION(BlueprintCallable, Category = "Donkey Kong | Player")
		void Restart();

	void GameOver();

	inline int32 GetLevelScore() { return BaseLevelScore; }

private:
	/* Subtracts bonus score, over period of time. */
	UFUNCTION()
		void SubtractScore();
};



