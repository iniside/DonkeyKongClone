// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "DonkeyKongGameMode.generated.h"

UCLASS(minimalapi)
class ADonkeyKongGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADonkeyKongGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Score")
		int32 BonusLevelScore;
	/*
		Base score for level, it's subtracted over time.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Score")
		int32 BaseLevelScore;

	/*
		Time in seconds, between score subtraction.
	*/
	UPROPERTY(EditAnywhere, Category = "Config")
		float HowOftenSubtractScore;
	/*
		This level will be opened when player press Restart Button.
	*/
	UPROPERTY(EditAnywhere, Category = "Config")
		FName FirstLevelName;

	/*
		How much score will be subtracted on each period.
	*/
	UPROPERTY(EditAnywhere, Category = "Score")
		int32 SubtractionAmount;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class ADKLevelMaster* MasterLevel;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class UDKGameInstance* GameInstance;

private:
	FTimerHandle ScoreSubtractionTimeHandle;
public:
	void AddScore(int32 ScoreIn);

	/*
		Called when played die.
	*/
	void PlayerDied(class ADonkeyKongCharacter* CharacterIn);
	/*
		Called when played die.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
		void OnPlayerDied(class ADonkeyKongCharacter* CharacterIn);


	UFUNCTION(BlueprintCallable, Category = "Player")
		void RespawnPlayer(class ADonkeyKongCharacter* CharacterIn, class ADKPlayerController* PCIn);

	UFUNCTION(BlueprintCallable, Category = "Player")
		void Restart();

protected:
	UFUNCTION()
		void SubtractScore();
};



