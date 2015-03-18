// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKPlayerController.h"


ADKPlayerController::ADKPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ADKPlayerController::AddScore(const FVector& TargetLocationIn, int32 ScoreIn)
{
	OnScoreAdded(TargetLocationIn, ScoreIn);
}