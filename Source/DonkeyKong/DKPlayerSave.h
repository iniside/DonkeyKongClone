// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "DKPlayerSave.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_API UDKPlayerSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Player Info")
		FDKCharacterData CharacterData;
};
