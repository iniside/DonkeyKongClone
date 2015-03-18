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
	
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Score")
		int32 TotalGameScore;
};
