// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKFallingPlatform.generated.h"
/*
	BAse class for falling platform.
*/
UCLASS()
class DONKEYKONG_API ADKFallingPlatform : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic")
		UBillboardComponent* BillRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic")
		UStaticMeshComponent* Mesh;

protected:
	FVector LastLocation;
public:	
	// Sets default values for this actor's properties
	ADKFallingPlatform();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void Reset() override;

	/* Called when this platform is supposed to fall. Usually on level end. */
	void PlatformFall();
	

	UFUNCTION(BlueprintImplementableEvent, Category = "Donkey Kong")
		void OnPlatformFall();
};
