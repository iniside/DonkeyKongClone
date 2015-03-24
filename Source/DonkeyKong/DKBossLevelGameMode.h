// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DonkeyKongGameMode.h"
#include "DKBossLevelGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDKOnPlatformHolderRemoved, class ADKPlatformHolder*);

/**
 * 
 */
UCLASS()
class DONKEYKONG_API ADKBossLevelGameMode : public ADonkeyKongGameMode
{
	GENERATED_BODY()
public:
	ADKBossLevelGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	
protected:
	/* All platform hodres in current level. */
	UPROPERTY()
		TArray<class ADKPlatformHolder*> PlatformHolders;
	/* All falling platforms in current level. */
	UPROPERTY()
		TArray<class ADKFallingPlatform*> FallingPlatforms;

public:
	FDKOnPlatformHolderRemoved OnPlatformHolderRemoved;
public:
	virtual void Restart() override;

	/* Called when no PlatformHolders are left in level. */
	void FinishLevel();
protected:
	/* Removes PlatformHolder from level and checks how many platform left in level. */
	UFUNCTION()
	void RemovePlatformHolder(class ADKPlatformHolder* Platform);

	/* Sets game mode specific actors for this game mode. */
	void SetupLevelActors();
};
