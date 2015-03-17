// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKEnemy.h"
#include "DKSimpleEnemy.generated.h"

UCLASS()
class DONKEYKONG_API ADKSimpleEnemy : public ADKEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADKSimpleEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
