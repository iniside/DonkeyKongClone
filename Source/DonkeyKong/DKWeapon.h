// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKWeapon.generated.h"
/*
	Very simple weapon. When picked it will attach itself in front of character,
	and starts auto attacking at set intervals, after X number of enemies is destroyed weapon
	braks and is destroyed as well.

	Weapon is also destroyed when character attemps to climb ladder.
*/
UCLASS()
class DONKEYKONG_API ADKWeapon : public AActor
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
	/* Maximum number of enemies killed, before weapon will be destroyed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		int32 MaximumKilledEnemies;
	
	/* Time between auto attacks. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float AttackInterval;

	/* How far infront of character weapon will strike. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float Range;

	/* Radius of capsule used to detect if enemy is present. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float CapsuleRadius;

	/* Half height of capsule used to detect if enemy is present. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float CapsuleHalfHeight;
	/*  */
	UPROPERTY(EditAnywhere, Category = "Config")
		TArray<TEnumAsByte<ECollisionChannel> > EnemyCollisionType;

	UPROPERTY()
	class ADonkeyKongCharacter* DKOwner;

private:
	FTimerHandle AttackIntervalTimerHandle;
	int32 CurrentKilledEnemies;
	FCollisionObjectQueryParams EnemiesTypes;
public:	
	// Sets default values for this actor's properties
	ADKWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	/*
		Activate weapon and attach it to character.

		OwnerIn - Character which took weapon.
	*/
	void ActivateWeapon(class ADonkeyKongCharacter* OwnerIn);
protected:
	UFUNCTION()
		void AutoAttack();

	void StopWeapon();
};
