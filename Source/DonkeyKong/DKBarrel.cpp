// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKBarrel.h"


// Sets default values
ADKBarrel::ADKBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADKBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKBarrel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

