#pragma once

#include "CoreMinimal.h"
#include "Character/Component/MJSkillComponentBase.h"
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
	uint8 CurrentDungeonMapNum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FSkillData> CurrentOwnedSkillMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayTag> CurrentEquippedSkillMap;


	void SetCurrentOwnedSKillMap(TMap<FGameplayTag, FSkillData> Input)
	{
		CurrentOwnedSkillMap.Empty();
		for (auto Iter : Input)
		{
			CurrentOwnedSkillMap.Add(Iter);
		}
	}
	
	void SetCurrentEquippedSkillMap(TMap<FGameplayTag, FGameplayTag> Input)
	{
		CurrentEquippedSkillMap.Empty();
		for (auto Iter : Input)
		{
			CurrentEquippedSkillMap.Add(Iter);
		}
	}

};
