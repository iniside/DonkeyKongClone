// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DKGlobalTypes.h"
#include "GameFramework/SaveGame.h"
#include "DKSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_API UDKSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	/* Global score. */
	UPROPERTY(VisibleAnywhere, Category = "Ladderboard")
		TArray<FDKScoreLadder> LadderScore;

	UPROPERTY(VisibleAnywhere, Category = "Basic")
		FString SaveSlotName;
public:
	UDKSaveGame(const FObjectInitializer& ObjectInitializer);
};
