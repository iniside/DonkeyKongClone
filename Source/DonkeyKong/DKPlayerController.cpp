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

	DKPlayerState->SetCurrentLevel(MasterLevel->GetCurrentLevelName());

	LoadCharacterData();
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
}

void ADKPlayerController::PlayerDied()
{
	DKPlayerState->RemoveOneLife();
	DKPlayerState->SetCurrentLevel(MasterLevel->GetCurrentLevelName());
	SaveCharacterData();
}

void ADKPlayerController::Respawn()
{
	DKGameMode->ResetLevel();
	DKGameMode->Restart();
	if (DKPlayerState->GetCurrentLifes() > 0)
	{
		ADonkeyKongCharacter* Char = Cast<ADonkeyKongCharacter>(GetPawn());
		if (!Char)
		{
			if (GameInstance->PlayerNumber > 1)
			{
				if (!(MasterLevel->GetCurrentLevelName() == DKPlayerState->GetCurrentLevel()))
				{
					RespawnOnDifferentLevel();
					return;
				}
			}
			
			AActor* PlayerStart = DKGameMode->FindPlayerStart(this);
			if (!PlayerStart)
				return;

			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoCollisionFail = true;

			ADonkeyKongCharacter* NewChar = GetWorld()->SpawnActor<ADonkeyKongCharacter>(DKGameMode->DefaultPawnClass,
				PlayerStart->GetActorLocation(), FRotator(0, 0, 0), SpawnParams);
			Possess(NewChar);
			OnCharacterRespawned();
			
			MasterLevel->OnCharacterRespawned.Broadcast(this);
		}
	}
}

void ADKPlayerController::RespawnOnDifferentLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), DKPlayerState->GetCurrentLevel());
}

void ADKPlayerController::Spectate()
{
	//if there is more than player we will alter between them.
	//and do it in advance, so we can have data available in spectator mode.
	SwapPlayers();

	LoadCharacterData();

	//check if player finished game.
 	if (DKPlayerState->GetFinishedGame())
	{
		//if true, we will iterate over all players to find the one which does not finished game
		//or until we run out of players.
		int32 CurrentChecks = 0;
		while (CurrentChecks < GameInstance->PlayerNumber)
		{
			SwapPlayers();
			LoadCharacterData();
			if (!DKPlayerState->GetFinishedGame())
				break;
			CurrentChecks++;
		}
	}
	if (DKPlayerState->GetFinishedGame() )
	{
		DKGameMode->GameOver();
		OnGameOver();
	}
	else if (DKPlayerState->GetCurrentLifes() > 0)
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

void ADKPlayerController::MoveToNextLevel(int32 BonusScore)
{
	DKPlayerState->AddScore(BonusScore);
	DKPlayerState->SetCurrentLevel(MasterLevel->GetNextLevelName());
	SaveCharacterData();
}

void ADKPlayerController::FinishGame(int32 ScoreIn)
{
	DKPlayerState->AddScore(ScoreIn);
	DKPlayerState->SetFinishedGame(true);
	SaveCharacterData();
	if (GameInstance->HaveTwoPlayers())
	{
		//else move to another player.
		Spectate();
	}
	else
	{
		//if there is only one player, just finish game.
		OnGameOver();
	}
}

void ADKPlayerController::QuitCurrentGame()
{
	
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
		FDKCharacterData data = UDKBlueprintFunctionLibrary::LoadPlayerTwo();
		DKPlayerState->LoadStateFromSave(data);
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
		UDKBlueprintFunctionLibrary::SavePlayerTwo(DKPlayerState->GetCurrentCharacterData());
	}
}

void ADKPlayerController::SwapPlayers()
{
	GameInstance->SwapPlayers();
}