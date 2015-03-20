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

public:
	ADKPlayerController(const FObjectInitializer& ObjectInitializer);

	/** AActor Overrieds - BEGIN */
	virtual void BeginPlay() override;
	/* AActor Overrieds - END **/

	/* Add score to player per level and per session. */
	UFUNCTION(BlueprintCallable, Category = "Score")
		virtual void AddScore(int32 PlayerIndex, const FVector& TargetLocationIn, int32 ScoreIn);
	
	/* Called when score is added to player. */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Score")
		void OnScoreAdded(int32 PlayerIndex, const FVector& TargetLocation, int32 Score);

	/** APlayerController Overried - BEGIN */
	virtual void SetupInputComponent() override;
	/* APlayerController Overried - BEGIN **/
	
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
		void OnGameOver();
};
