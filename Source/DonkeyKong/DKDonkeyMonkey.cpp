// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKDonkeyMonkey.h"


// Sets default values
ADKDonkeyMonkey::ADKDonkeyMonkey()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADKDonkeyMonkey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKDonkeyMonkey::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ADKDonkeyMonkey::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

