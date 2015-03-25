// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DKEnemy.h"
#include "DKSimpleEnemy.generated.h"
/*
	Simple enemy patrols platform, and move up-down ladder, but does not focus on player.
	It just randomly moves around.
*/
UCLASS()
class DONKEYKONG_API ADKSimpleEnemy : public ADKEnemy
{
	GENERATED_BODY()
protected:
	/* How fast enemy will move */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float MovementSpeed;

	UPROPERTY(EditAnywhere, Category = "Config")
		TArray<TEnumAsByte<ECollisionChannel> > FloorToTrace;

	FCollisionObjectQueryParams FloorColiision;

	/* Minimum distance in which enemy should search for next nav point */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float MinSearchDistance;
	
	/* Maximum distance in which enemy should search for next nav point */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float MaxSearchDistance;
private:
	/* In which direction, I'm currently moving. */
	float CurrentMoveDireaction;
	/* Where I should go. */
	FVector PointToMove;
	/* -1 - down, 1 - up*/
	float ClimbingDirection;
	/* Am I currently climbing ? */
	bool bIsClimbing;
	/* Ladder this actor is currently climbing on. */
	UPROPERTY()
	class ADKLadder* CurrentLadder;

public:
	// Sets default values for this actor's properties
	ADKSimpleEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/* Searches for floor when moving on flat surface */
	bool SearchForFloor(FHitResult& HitOut);

	/* searches random point in front or back of enemy to move to. */
	bool FindPointToMove(FHitResult& HitOut);

	/** ADKEnemy overrides - BEGIN */

	/* Call to tell enemy to climb up */
	virtual void ClimbUp(class ADKLadder* LadderIn) override;

	/* Call to tell enemey to climb down */
	virtual void ClimbDown(class ADKLadder* LadderIn) override;

	/* Call to tell enemy, to stop climbing */
	virtual void ClimbStop(class ADKLadder* LadderIn) override;

	/* ADKEnemy overrides - END **/

	/* Kill enemy. */
	virtual void Kill(class ADKPlayerController* WhoKilled) override;
};
