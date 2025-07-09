#pragma once

#include "CoreMinimal.h"
#include "MJDungeonGraphStruct.h"
#include "MJDungeonSessionDataStruct.generated.h"

UENUM(BlueprintType)
enum class EMJDungeonContext : uint8
{
	InActive			UMETA(DisplayName = "InActive"),
	Activated			UMETA(DisplayName = "Activated"),
	Cleared				UMETA(DisplayName = "Cleared")
};

USTRUCT(BlueprintType)
struct FMJDungeonActorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<AActor> ActorClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform Transform;
};


USTRUCT(BlueprintType)
struct FMJDungeonSessionData
{
	GENERATED_BODY()
	
	FMJDungeonSessionData(EMJDungeonContext InContext, uint8 InNodeNum, EMJAISpawnType InAISpawnType, const FString& InMapName)
	: DungeonContext(InContext)
	, DungeonNodeNum(InNodeNum)
	, AISpawnType(InAISpawnType)
	, MapName(InMapName)
	{}
	
	FMJDungeonSessionData()
		: DungeonContext(EMJDungeonContext::InActive)
		, DungeonNodeNum(0)
		, AISpawnType(EMJAISpawnType::Static)
		, MapName(TEXT(""))
	{}

	UPROPERTY(BlueprintReadOnly)
	EMJDungeonContext DungeonContext = EMJDungeonContext::InActive;
	
	UPROPERTY(BlueprintReadOnly)
	uint8 DungeonNodeNum;

	UPROPERTY(BlueprintReadOnly)
	EMJAISpawnType AISpawnType;

	UPROPERTY(BlueprintReadOnly)
	FString MapName;

	UPROPERTY(BlueprintReadOnly)
	TArray<FMJDungeonActorInfo> SpawnInfos;
	
};
