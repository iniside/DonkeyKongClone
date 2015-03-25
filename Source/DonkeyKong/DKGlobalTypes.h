// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "DKGlobalTypes.generated.h"

USTRUCT(BlueprintType)
struct DONKEYKONG_API FDKScoreLadder
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		FString PlayerName;
	UPROPERTY(BlueprintReadOnly)
		int32 PlayerScore;

	FDKScoreLadder()
	{};
	FDKScoreLadder(const FString& PlayerNameIn, int32 PlayerScoreIn)
		: PlayerName(PlayerNameIn),
		PlayerScore(PlayerScoreIn)
	{};

	inline bool operator<(const FDKScoreLadder& Other) const
	{
		return Other.PlayerScore < PlayerScore;
	}
	inline bool operator>(const FDKScoreLadder& Other) const
	{
		return Other.PlayerScore > PlayerScore;
	}
	inline bool operator==(const FDKScoreLadder& Other) const
	{
		return PlayerScore == Other.PlayerScore;
	}
};

USTRUCT(BlueprintType)
struct DONKEYKONG_API FDKCharacterData
{
	GENERATED_USTRUCT_BODY()
public:
	/* Current lifes of player. */
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentLifes;

	/* Current score achieved by player */
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentScore;

	/* Last level reaced by player. Player will be respawned on this level. */
	UPROPERTY(BlueprintReadOnly)
		FName CurrentLevel;
	/* Did player finished game ? */
	UPROPERTY(BlueprintReadOnly)
		bool bFinishedGame;

	FDKCharacterData()
		: CurrentLifes(0),
		CurrentScore(0),
		bFinishedGame(false)
	{};

	FDKCharacterData(int32 CurrentLifesIn, int32 CurrentScoreIn, FName CurrentLevelIn)
		: CurrentLifes(CurrentLifesIn),
		CurrentScore(CurrentScoreIn),
		CurrentLevel(CurrentLevelIn),
		bFinishedGame(false)
	{};

	FDKCharacterData(int32 CurrentLifesIn, int32 CurrentScoreIn, FName CurrentLevelIn, bool bFinishedGameIn)
		: CurrentLifes(CurrentLifesIn),
		CurrentScore(CurrentScoreIn),
		CurrentLevel(CurrentLevelIn),
		bFinishedGame(bFinishedGameIn)
	{};
};

struct FSaveSlot
{
public:
	FString SlotName;
	int32 UserIndex;

	FSaveSlot()
	{};

	FSaveSlot(const FString& SlotNameIn, int32 UserIndexIn)
		: SlotName(SlotNameIn),
		UserIndex(UserIndexIn)
	{};

	inline void operator=(const FSaveSlot& Other)
	{
		SlotName = Other.SlotName;
		UserIndex = Other.UserIndex;
	}
};

USTRUCT()
struct FSaveSlotNames
{
	GENERATED_USTRUCT_BODY()
public:
	static const FSaveSlot LadderBoardSlot;

	static const FSaveSlot PlayerOneSlot;

	static const FSaveSlot PlayerTwoSlot;
};