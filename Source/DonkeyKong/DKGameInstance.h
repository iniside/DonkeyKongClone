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
		int32 TotalGameScore;

	UPROPERTY(EditAnywhere, Category = "Player")
		int32 StartingLifes;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
		int32 PlayerLifes;

public:
	void AddScore(int32 ScoreIn);
	void SubtractScore(int32 ScoreIn);

	void SubtractPlayerLife();

	inline int32 GetPlayerLifes() { return PlayerLifes; }

	void ResetCurrentGame();
};
