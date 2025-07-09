#pragma once

#include "CoreMinimal.h"
#include "MJDungeonGraphStruct.generated.h"

UENUM()
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

	UPROPERTY(BlueprintReadOnly)
	int32 NodeID;

	UPROPERTY(BlueprintReadOnly)
	int32 AssignedMapID;

	UPROPERTY(BlueprintReadOnly)
	ENodeType NodeType;

	UPROPERTY(BlueprintReadOnly)
	FVector2D UICoordinate;

	UPROPERTY(BlueprintReadOnly)
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

	UPROPERTY(BlueprintReadOnly)
	TArray<FDungeonNode> Nodes;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector2D> BezierPoints;

	UPROPERTY(BlueprintReadOnly)
	int32 StartNodeID = -1;

	UPROPERTY(BlueprintReadOnly)
	int32 BossNodeID = -1;
};