// Fill out your copyright notice in the Description page of Project Settings.

#include "DonkeyKong.h"
#include "DKSaveGame.h"

UDKSaveGame::UDKSaveGame(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SaveSlotName = FSaveSlotNames::LadderBoardSlot.SlotName;
}