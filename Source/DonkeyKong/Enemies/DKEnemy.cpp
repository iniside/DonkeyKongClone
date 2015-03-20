// Fill out your copyright notice in the Description page of Project Settings.

#include "../DonkeyKong.h"
#include "DKEnemy.h"


// Sets default values
ADKEnemy::ADKEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ScoreForJumping = 100;

}

// Called when the game starts or when spawned
void ADKEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

