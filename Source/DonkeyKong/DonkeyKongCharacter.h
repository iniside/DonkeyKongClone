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

	UPROPERTY()
	class ADKEnemy* LastEnemy;

	UPROPERTY()
	class ADKWeapon* EquipedWeapon;

protected:
	/** AActor overrides BEIGN */
	virtual void BeginPlay() override;
	virtual void Destroy() override;
	/* AActor overrides END **/
	
	/** Called for side to side input */
	void MoveRight(float Val);

	/* Called to climb over ladder */
	void Climb(float Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	// End of APawn interface

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
public:
	ADonkeyKongCharacter(const FObjectInitializer& ObjectInitializer);

	inline class ADKPlayerController* GetDKPC() const { return DKPC; };
	
	/* Called when character reached end of ladder. */
	void ClimbFinish(const FVector& LeaveLedderLocation);

	/* Called when character died (obviously ?). */
	void CharacterDied();
	/* Get current climbing direction on ladder */
	inline float GetClimbingDirection() { return ClimbingDirection; };
	
	/* Equip Weapon */
	void EquipWeapon(class ADKWeapon* WeaponIn);

	/* Unequip current weapon. */
	void UnEquipWeapon();

	bool HaveWeapon();
};
