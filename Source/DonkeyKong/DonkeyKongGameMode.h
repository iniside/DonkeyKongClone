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
		How much score will be subtracted on each period.
	*/
	UPROPERTY(EditAnywhere, Category = "Score")
		int32 SubtractionAmount;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class ADKLevelMaster* MasterLevel;

private:
	FTimerHandle ScoreSubtractionTimeHandle;
public:
	void AddScore(int32 ScoreIn);

protected:
	UFUNCTION()
		void SubtractScore();
};



