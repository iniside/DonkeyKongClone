// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKFallingPlatform.h"


// Sets default values
ADKFallingPlatform::ADKFallingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BillRoot = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillRoot"));
	RootComponent = BillRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	LastLocation = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void ADKFallingPlatform::BeginPlay()
{
	Super::BeginPlay();
	LastLocation = GetActorLocation();
}

// Called every frame
void ADKFallingPlatform::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ADKFallingPlatform::Reset()
{
	SetActorLocation(LastLocation);
}

void ADKFallingPlatform::PlatformFall()
{
	AddActorLocalOffset(FallLocation);
	//SetActorEnableCollision(false);
	//SetActorHiddenInGame(true)
	OnPlatformFall();
}