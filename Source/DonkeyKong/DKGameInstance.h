// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "DKGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_API UDKGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UDKGameInstance(const FObjectInitializer& ObjectInitializer);
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Score")
		TArray<int32> TotalGameScore;

	UPROPERTY(EditAnywhere, Category = "Player")
		TArray<int32> StartingLifes;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
		TArray<int32> PlayerLifes;

public:
	void AddScore(int32 PlayerIndex, int32 ScoreIn);
	void SubtractScore(int32 PlayerIndex, int32 ScoreIn);

	void SubtractPlayerLife(int32 PlayerIndex);

	inline int32 GetPlayerLifes(int32 PlayerIndex) { return PlayerLifes[PlayerIndex]; }

	void ResetCurrentGame();
};
