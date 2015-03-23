// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKWeaponPickup.generated.h"

UCLASS()
class DONKEYKONG_API ADKWeaponPickup : public AActor
{
	GENERATED_BODY()
protected:
	/*
		Will use it to detect if character overlaped this weapon. If did, we will attach weapon to character
		and activate it.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		USphereComponent* Collision;

	/* Weapon mesh. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		UStaticMeshComponent* Mesh;

protected:
	/* Weapon which will be given to player. */
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<class ADKWeapon> WeaponPick;

private:
	/* Indicator if weapon has already been picked from here. */
	bool bPickedWeapon;
public:	
	// Sets default values for this actor's properties
	ADKWeaponPickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void Reset() override;

protected:
	UFUNCTION()
		void Collision_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
