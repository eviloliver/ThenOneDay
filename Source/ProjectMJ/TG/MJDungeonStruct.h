#pragma once

#include "CoreMinimal.h"
#include "MJDungeonStruct.generated.h"

UENUM(BlueprintType)
enum class ENodeType : uint8
{
	Battle UMETA(DisplayName = "Battle"),
	Reward UMETA(DisplayName = "Reward"),
	Boss UMETA(DisplayName = "Boss")
};

USTRUCT(BlueprintType)
struct FDungeonNode
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 NodeID;

	UPROPERTY(BlueprintReadWrite)
	int32 AssignedMapID;

	UPROPERTY(BlueprintReadWrite)
	ENodeType NodeType;

	UPROPERTY(BlueprintReadWrite)
	FVector2D UICoordinate;

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> ConnectedNodeIDs;

	static FString NodeTypeToString(ENodeType Type)
	{
		switch (Type)
		{
		case ENodeType::Battle:
			return TEXT("Battle");
		case ENodeType::Reward:
			return TEXT("Reward");
		case ENodeType::Boss:
			return TEXT("Boss");
		default:
			return TEXT("Unknown");
		}
	}
	
};

USTRUCT(BlueprintType)
struct FDungeonGraph
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FDungeonNode> Nodes;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector2D> BezierPoints;

	UPROPERTY(BlueprintReadWrite)
	int32 StartNodeID = -1;

	UPROPERTY(BlueprintReadWrite)
	int32 BossNodeID = -1;
};