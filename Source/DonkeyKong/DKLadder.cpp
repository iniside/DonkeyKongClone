// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKLadder.h"
#include "DonkeyKongCharacter.h"
// Sets default values
ADKLadder::ADKLadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	LadderBegin = CreateDefaultSubobject<UBoxComponent>(TEXT("LadderBegin"));
	LadderEnd = CreateDefaultSubobject<UBoxComponent>(TEXT("LadderEnd"));


	LadderBeginDrop = CreateDefaultSubobject<UBoxComponent>(TEXT("LadderBeginDrop"));
	LadderEndDrop = CreateDefaultSubobject<UBoxComponent>(TEXT("LadderEndDrop"));


	LadderBeginLocation = FVector::ZeroVector;
	LadderEndLocation = FVector::ZeroVector;

	LadderBegin->OnComponentBeginOverlap.AddDynamic(this, &ADKLadder::LadderBegin_BeginOverlap);
	LadderEnd->OnComponentBeginOverlap.AddDynamic(this, &ADKLadder::LadderEnd_BeginOverlap);

	LadderBeginDrop->OnComponentBeginOverlap.AddDynamic(this, &ADKLadder::LadderEnd_LadderBeginDrop);
	LadderEndDrop->OnComponentBeginOverlap.AddDynamic(this, &ADKLadder::LadderEnd_LadderEndDrop);
}

// Called when the game starts or when spawned
void ADKLadder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKLadder::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADKLadder::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	LadderBegin->SetRelativeLocation(LadderBeginLocation);
	LadderEnd->SetRelativeLocation(LadderEndLocation);

	LadderBeginDrop->SetRelativeLocation(LadderBeginDropLocation);
	LadderEndDrop->SetRelativeLocation(LadderEndDropLocation);
}



void ADKLadder::LadderBegin_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (ADonkeyKongCharacter* DKChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		LadderBeginDrop->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LadderEndDrop->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void ADKLadder::LadderEnd_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADonkeyKongCharacter* DKChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		LadderBeginDrop->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		LadderEndDrop->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADKLadder::LadderEnd_LadderBeginDrop(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADonkeyKongCharacter* DKChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		LadderBegin->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void ADKLadder::LadderEnd_LadderEndDrop(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADonkeyKongCharacter* DKChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		LadderBegin->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}