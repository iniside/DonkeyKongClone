// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKGameInstance.h"
#include "DKLevelMaster.h"


// Sets default values
ADKLevelMaster::ADKLevelMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	EndLevelTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("EndLevelTrigger"));
	EndLevelTrigger->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ADKLevelMaster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADKLevelMaster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
