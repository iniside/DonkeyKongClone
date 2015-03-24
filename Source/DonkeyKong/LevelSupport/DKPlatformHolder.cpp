// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "../DKBossLevelGameMode.h"
#include "../DonkeyKongCharacter.h"
#include "DKPlatformHolder.h"


// Sets default values
ADKPlatformHolder::ADKPlatformHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BillRoot = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillRoot"));
	RootComponent = BillRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ADKPlatformHolder::Mesh_BeginOverlap);

}

// Called when the game starts or when spawned
void ADKPlatformHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKPlatformHolder::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}



void ADKPlatformHolder::Reset()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}

void ADKPlatformHolder::DisableHolder()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void ADKPlatformHolder::Mesh_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADonkeyKongCharacter* MyChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		if (ADKBossLevelGameMode* BoxGM = Cast<ADKBossLevelGameMode>(GetWorld()->GetAuthGameMode()))
		{
			BoxGM->OnPlatformHolderRemoved.Broadcast(this);
		}
	}
}