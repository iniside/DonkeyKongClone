// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKPlatformHolder.generated.h"
/*
	Base class for holding togather platforms, which are supposed to fall.

	It actually doesn't hold platforms physically, but once all these actors have been removed 
	from level, all "holded" platforms will fall (or will be destroyed).

	As per boss level in DonkeyKong.
*/
UCLASS()
class DONKEYKONG_API ADKPlatformHolder : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic")
		UBillboardComponent* BillRoot;

	/* Mesh to display something in level. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic")
		UStaticMeshComponent* Mesh;
public:	
	// Sets default values for this actor's properties
	ADKPlatformHolder();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	/* Resets actor to previous state. */
	virtual void Reset() override;

	/* Disables holder after is has been crossed. */
	void DisableHolder();

	UFUNCTION()
	void Mesh_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
