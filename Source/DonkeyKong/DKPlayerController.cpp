// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DonkeyKongGameMode.h"
#include "DonkeyKongCharacter.h"
#include "DKGameInstance.h"
#include "DKPlayerState.h"
#include "DKGlobalTypes.h"
#include "DKBlueprintFunctionLibrary.h"
#include "LevelSupport/DKLevelMaster.h"

#include "DKPlayerController.h"


ADKPlayerController::ADKPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ADKPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	for (auto It = TActorIterator<ADKLevelMaster>(GetWorld()); It; ++It)
	{
		MasterLevel = *It;
		break;
	}
	GameInstance = Cast<UDKGameInstance>(GetGameInstance());
	DKGameMode = Cast<ADonkeyKongGameMode>(UGameplayStatics::GetGameMode(this));

	DKPlayerState = Cast<ADKPlayerState>(PlayerState);

	MasterLevel->OnCharacterRespawned.Broadcast(this);
}

void ADKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("RespawnPlayer", IE_Pressed, this, &ADKPlayerController::Respawn);
}

void ADKPlayerController::AddScore(const FVector& TargetLocationIn, int32 ScoreIn)
{
	OnScoreAdded(TargetLocationIn, ScoreIn);

	DKPlayerState->AddScore(ScoreIn);
	//GameInstance->AddScore(ScoreIn);
	
}

void ADKPlayerController::PlayerDied()
{
	DKPlayerState->RemoveOneLife();
	//DKPlayerState->SetCurrentLevel()
	SaveCharacterData();
}

void ADKPlayerController::Respawn()
{
	

	if (DKPlayerState->GetCurrentLifes() > 0)
	{
		ADonkeyKongCharacter* Char = Cast<ADonkeyKongCharacter>(GetPawn());
		if (!Char)
		{
			AActor* PlayerStart = DKGameMode->FindPlayerStart(this);
			if (!PlayerStart)
				return;
			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoCollisionFail = true;

			ADonkeyKongCharacter* NewChar = GetWorld()->SpawnActor<ADonkeyKongCharacter>(DKGameMode->DefaultPawnClass,
				PlayerStart->GetActorLocation(), FRotator(0, 0, 0), SpawnParams);
			Possess(NewChar);


			OnCharacterRespawned();
			DKGameMode->ResetLevel();
			MasterLevel->OnCharacterRespawned.Broadcast(this);
		}
	}
	//DKGameMode->RestartGame();
}
void ADKPlayerController::Spectate()
{
	//if there is more than player we will alter between them.
	//and do it in advance, so we can have data available in spectator mode.
	//hacky FIX IT!.
	if (GameInstance->PlayerNumber > 1)
	{
		if (GameInstance->CurrentPlayerIndex == 0)
			GameInstance->CurrentPlayerIndex = 1;
		else
			GameInstance->CurrentPlayerIndex = 0;
	}
	LoadCharacterData();

	if (GameInstance->AreAnyLifesRemaining())
	{
		OnStartSpectate();
	}
	else
	{
		DKGameMode->GameOver();
		OnGameOver();
	}
	ASpectatorPawn* spectate = GetWorld()->SpawnActor<ASpectatorPawn>(GetWorld()->GetAuthGameMode()->SpectatorClass);
	UnPossess();
	Possess(spectate);

	MasterLevel->OnCharacterRespawned.Broadcast(this);
}

void ADKPlayerController::QuitCurrentGame()
{
	GameInstance->ResetCurrentGame();
}

void ADKPlayerController::LoadCharacterData()
{
	if (GameInstance->CurrentPlayerIndex == 0)
	{
		FDKCharacterData data = UDKBlueprintFunctionLibrary::LoadPlayerOne();
		DKPlayerState->LoadStateFromSave(data);
	}
	else if (GameInstance->CurrentPlayerIndex == 1)
	{

	}
}

void ADKPlayerController::SaveCharacterData()
{
	if (GameInstance->CurrentPlayerIndex == 0)
	{
		UDKBlueprintFunctionLibrary::SavePlayerOne(DKPlayerState->GetCurrentCharacterData());
	}
	else if (GameInstance->CurrentPlayerIndex == 1)
	{

	}
}
