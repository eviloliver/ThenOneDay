#pragma once

#include "CoreMinimal.h"
#include "MJCharacterAttributeSaveDataStruct.h"
#include "MJCharacterSkillAttributeSaveData.h"
#include "MJPlayerSessionDataStruct.generated.h"

UENUM(BlueprintType)
enum class EMJGameplayContext : uint8
{
	InTown	   		UMETA(DisplayName = "InTown"),
	InDungeon  		UMETA(DisplayName = "InDungeon"),
	InHouse			UMETA(DisplayName = "InHouse"),
	InDialogue		UMETA(DisplayName = "InDialogue")
};

USTRUCT(BlueprintType)
struct FMJPlayerSessionData
{
	GENERATED_BODY()

	UPROPERTY()
	FString PlayerName;
	
	UPROPERTY()
	int32 PlayerLevel = 1;

	UPROPERTY()
	float PlayerExp = 0.0f;

	UPROPERTY()
	int8 SaveGameSlotNum = -1;

	UPROPERTY(BlueprintReadOnly)
	EMJGameplayContext GameplayContext;

	UPROPERTY(BlueprintReadOnly)
	FMJCharacterAttributeSaveData CharacterAttribute;

	UPROPERTY(BlueprintReadOnly)
	FMJCharacterSkillAttributeSaveData CharacterSkillAttribute;
	
	UPROPERTY(BlueprintReadOnly)
	uint8 CurrentDungeonMapNum;

};
