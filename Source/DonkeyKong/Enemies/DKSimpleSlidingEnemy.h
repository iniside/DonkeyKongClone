// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKEnemy.h"
#include "DKSimpleSlidingEnemy.generated.h"
/*
	Very simple sliding enemy. Does't have any AI, just slide in one direction until end of platform
	or until trap. In case of trap, enemy fall to it and is destroyed, in case of level and enemy will just
	start moving in opposite direction.
*/
UCLASS()
class DONKEYKONG_API ADKSimpleSlidingEnemy : public ADKEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADKSimpleSlidingEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
