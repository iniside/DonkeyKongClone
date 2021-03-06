// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DKEnemy.h"
#include "GameFramework/Pawn.h"
#include "DKDonkeyMonkey.generated.h"

/*
	Placeholder for Monkey which does look like Donkey.
*/

UCLASS()
class DONKEYKONG_API ADKDonkeyMonkey : public ADKEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADKDonkeyMonkey();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
