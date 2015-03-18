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

void ADKPlayerController::AddScore(const FVector& TargetLocationIn, int32 ScoreIn)
{
	OnScoreAdded(TargetLocationIn, ScoreIn);

	DKGameMode->AddScore(ScoreIn);
}