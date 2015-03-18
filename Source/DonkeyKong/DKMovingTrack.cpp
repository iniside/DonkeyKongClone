// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DonkeyKongCharacter.h"
#include "DKMovingTrack.h"


// Sets default values
ADKMovingTrack::ADKMovingTrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	TrackVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TrackVolume"));
	TrackVolume->AttachTo(RootComponent);

	TrackVolume->OnComponentBeginOverlap.AddDynamic(this, &ADKMovingTrack::TrackVolume_BeginOverlap);
	TrackVolume->OnComponentEndOverlap.AddDynamic(this, &ADKMovingTrack::TrackVolume_EndOverlap);
}

// Called when the game starts or when spawned
void ADKMovingTrack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKMovingTrack::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADKMovingTrack::TrackVolume_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADonkeyKongCharacter* MyChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		AffectedCharacters.AddUnique(MyChar);
	}
}

void ADKMovingTrack::TrackVolume_EndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ADonkeyKongCharacter* MyChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		AffectedCharacters.RemoveSwap(MyChar);
	}
}