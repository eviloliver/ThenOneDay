#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(BlueprintReadOnly)
	EMJGameplayContext GameplayContext;
	
	UPROPERTY(BlueprintReadOnly)
	uint8 CurrentDungeonMapNum;

};
