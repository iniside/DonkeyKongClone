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
	
public:
	ADKPlayerController(const FObjectInitializer& ObjectInitializer);


	virtual void BeginPlay() override;
	/*
		Add score to player per level and per session.
	*/
	UFUNCTION(BlueprintCallable, Category = "Score")
		virtual void AddScore(int32 PlayerIndex, const FVector& TargetLocationIn, int32 ScoreIn);
	/*
		Called when score is added to player.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Score")
		void OnScoreAdded(int32 PlayerIndex, const FVector& TargetLocation, int32 Score);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class ADonkeyKongGameMode* DKGameMode;


	UPROPERTY(BlueprintReadOnly, Category = "Base")
		int32 PlayerIndex;


};
