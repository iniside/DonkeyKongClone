// Fill out your copyright notice in the Description page of Project Settings.

#include "../DonkeyKong.h"
#include "DKSimpleSlidingEnemy.h"


// Sets default values
ADKSimpleSlidingEnemy::ADKSimpleSlidingEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADKSimpleSlidingEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKSimpleSlidingEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

