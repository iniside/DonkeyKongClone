// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "DonkeyKongCharacter.generated.h"

UCLASS(config=Game)
class ADonkeyKongCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* EnemyDetection;

	/* Component to which Equiped weapon will be attached. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		USceneComponent* WeaponAttachPoint;
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Move State")
		bool bIsClimbing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing")
		FVector ClimbDirection;

	/* Current climbing direction on ladder. */
	float ClimbingDirection;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class ADKLevelMaster* MasterLevel;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class ADKPlayerController* DKPC;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class ADonkeyKongGameMode* GameMode;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	class UDKGameInstance* GameInstance;

	/* Last enemy, over which character jumped. To prevent scoring from the same evenmy over and over. */
	UPROPERTY()
	class ADKEnemy* LastEnemy;

	/* Currently equiped weapon. */
	UPROPERTY()
	class ADKWeapon* EquipedWeapon;

	/* Ladder character is currently climbing on. */
	UPROPERTY()
	class ADKLadder* CurrentLadder;

	/* Ladder collision object type. */
	UPROPERTY(EditAnywhere, Category = "Config")
		TArray<TEnumAsByte<ECollisionChannel> > LadderToTrace;

	FCollisionObjectQueryParams LadderPrams;

	bool bHaveJumped;
	bool bHaveClimbed;
	FVector LastLocation;
public:
	ADonkeyKongCharacter(const FObjectInitializer& ObjectInitializer);
	
	/** AActor overrides BEIGN */
	virtual void BeginPlay() override;
	/* AActor overrides END **/

	/** AActor overrides BEIGN */
	
	/* Overrided to kill character when fallen from current platform. */
	virtual void Landed(const FHitResult& Hit) override;
	
	/* Called when character started falling. */
	virtual void Falling() override;
	/* AActor overrides END **/

	/** UObject overrides BEIGN */
	virtual void BeginDestroy() override;
	/* UObject overrides END **/

	inline class ADKPlayerController* GetDKPC() const { return DKPC; };

	/* Called when character reached end of ladder. */
	void ClimbFinish(const FVector& LeaveLedderLocation, class ADKLadder* Ladder);

	/* Called when character died (obviously ?). */
	void CharacterDied();

	/* Get current climbing direction on ladder */
	inline float GetClimbingDirection() { return ClimbingDirection; };

	/* Equip Weapon */
	void EquipWeapon(class ADKWeapon* WeaponIn);

	/* Unequip current weapon. */
	void UnEquipWeapon();

	/* Does character have weapon equiped ? */
	bool HaveWeapon();
	
	/////////
	///Input

	/** Called for side to side input */
	void MoveRight(float Val);

	/* Called to climb over ladder */
	void Climb(float Value);

	/* Searches for ladder. */
	void InputLookForLadder();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	// End of APawn interface

protected:
	/* Triggered when we jump over any object derived from ADKEnemy class. */
	UFUNCTION()
	void EnemyDetection_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/*
		Triggered when capsule touch any object derived from ADKEnemy class.

		Instant death.
	*/
	UFUNCTION()
		void Capsule_BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
