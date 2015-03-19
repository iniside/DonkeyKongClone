// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DonkeyKongGameMode.h"
#include "DKPlayerController.h"


ADKPlayerController::ADKPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ADKPlayerController::BeginPlay()
{
	Super::BeginPlay();

	DKGameMode = Cast<ADonkeyKongGameMode>(UGameplayStatics::GetGameMode(this));
}

void ADKPlayerController::AddScore(int32 PlayerIndex, const FVector& TargetLocationIn, int32 ScoreIn)
{
	OnScoreAdded(PlayerIndex, TargetLocationIn, ScoreIn);

	DKGameMode->AddScore(PlayerIndex, ScoreIn);
}