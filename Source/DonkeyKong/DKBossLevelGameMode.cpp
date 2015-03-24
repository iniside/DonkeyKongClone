// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"

#include "LevelSupport/DKFallingPlatform.h"
#include "LevelSupport/DKPlatformHolder.h"

#include "DKBossLevelGameMode.h"



ADKBossLevelGameMode::ADKBossLevelGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OnPlatformHolderRemoved.AddUObject(this, &ADKBossLevelGameMode::RemovePlatformHolder);
	
}

void ADKBossLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	//find all relevelant level elements.
	SetupLevelActors();
}

void ADKBossLevelGameMode::RemovePlatformHolder(class ADKPlatformHolder* Platform)
{
	PlatformHolders.RemoveSingle(Platform);
	PlatformHolders.Shrink();
	Platform->DisableHolder();
	
	if (PlatformHolders.Num() <= 0)
	{
		FinishLevel();
	}
}

void ADKBossLevelGameMode::Restart()
{
	Super::Restart();
	SetupLevelActors();
}

void ADKBossLevelGameMode::FinishLevel()
{
	for (ADKFallingPlatform* fallPlat : FallingPlatforms)
	{
		fallPlat->PlatformFall();
	}
}

void ADKBossLevelGameMode::SetupLevelActors()
{
	PlatformHolders.Empty();
	for (auto It = TActorIterator<ADKPlatformHolder>(GetWorld()); It; ++It)
	{
		PlatformHolders.Add(*It);
	}
	FallingPlatforms.Empty();
	for (auto It = TActorIterator<ADKFallingPlatform>(GetWorld()); It; ++It)
	{
		FallingPlatforms.Add(*It);
	}
}