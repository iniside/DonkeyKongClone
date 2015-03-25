// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DonkeyKongCharacter.h"
#include "DKPlayerController.h"
#include "DKGameInstance.h"
#include "DKPickup.h"


// Sets default values
ADKPickup::ADKPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->AttachTo(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADKPickup::Collision_BeginOverlap);
}

// Called when the game starts or when spawned
void ADKPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKPickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADKPickup::Reset()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}

void ADKPickup::Collision_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADonkeyKongCharacter* MyChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		UDKGameInstance* GI = Cast<UDKGameInstance>(GetGameInstance());
		MyChar->GetDKPC()->AddScore(GetActorLocation(), ScoreAwarded);

		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
	}
}