// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKSimpleEnemy.h"


// Sets default values
ADKSimpleEnemy::ADKSimpleEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADKSimpleEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKSimpleEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

