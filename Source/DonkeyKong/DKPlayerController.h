// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DKPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_API ADKPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class ADonkeyKongGameMode* DKGameMode;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class ADKLevelMaster* MasterLevel;


	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class UDKGameInstance* GameInstance;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class ADKPlayerState* DKPlayerState;

public:
	ADKPlayerController(const FObjectInitializer& ObjectInitializer);

	/** AActor Overrieds - BEGIN */
	virtual void BeginPlay() override;
	/* AActor Overrieds - END **/

	/* Add score to player per level and per session. */
	UFUNCTION(BlueprintCallable, Category = "Score")
		virtual void AddScore(const FVector& TargetLocationIn, int32 ScoreIn);
	
	/* Called when score is added to player. */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Score")
		void OnScoreAdded(const FVector& TargetLocation, int32 Score);

	/** APlayerController Overried - BEGIN */
	virtual void SetupInputComponent() override;
	/* APlayerController Overried - BEGIN **/
	
	/* Called when player died, to save current state of current player. */
	void PlayerDied();

	/*
		Respawn player.
		If in two player mode, it will alternate between player 1 and 2.
	*/
	void Respawn();
	
	/* Start spectating map, after player have been killed. */
	void Spectate();
	
	/* Quits current game. All progress will be lost! */
	UFUNCTION(BlueprintCallable, Category = "DonkeyKong|Game")
		void QuitCurrentGame();

	/* Called when player is out of lifes to respawn. */
	UFUNCTION(BlueprintImplementableEvent)
		void OnPlayerNoLifes();

	/* Called when player is killed, and start spectating map. */
	UFUNCTION(BlueprintImplementableEvent)
		void OnStartSpectate();

	/* Called when player is killed, and start spectating map. */
	UFUNCTION(BlueprintImplementableEvent)
		void OnCharacterRespawned();

	/* Called when player is killed, and start spectating map. */
	UFUNCTION(BlueprintImplementableEvent)
		void OnGameOver();

public:
	/* Loades character data from save to PlayerState after respawn. */
	void LoadCharacterData();

	/* Save character data for current player. */
	void SaveCharacterData();
};
