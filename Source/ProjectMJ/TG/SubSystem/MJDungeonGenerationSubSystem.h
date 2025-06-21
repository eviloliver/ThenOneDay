// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJDungeonStruct.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MJDungeonGenerationSubSystem.generated.h"

/**
 * Class Description: GameInstance Subsystem generates DungeonGraph
 * Author: Cha Tae Gwan
 * Created Date: 2025-06-20
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-06-20
 */
UCLASS()
class PROJECTMJ_API UMJDungeonGenerationSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UMJDungeonGenerationSubSystem();

	
	UFUNCTION(BlueprintCallable)
	bool GenerateDungeonGraph();

	UFUNCTION(BlueprintCallable)
	void SetSavedMapNodeNum(uint8 Input);

	
	UFUNCTION(BlueprintCallable)
	const FDungeonGraph& GetDungeonGraph() const { return DungeonGraph; }

	UFUNCTION(BlueprintPure, Category="Dungeon")
	uint8 GetMaxNodeNum() const;
	
	UFUNCTION(BlueprintCallable, Category="Dungeon")
	void SetMaxNodeNum(uint8 NewMaxNodeNum);

protected:
	
	// GeneratingDungeonSystem Section

	UPROPERTY(BlueprintReadOnly )
	FDungeonGraph DungeonGraph;
	
	UPROPERTY(VisibleAnywhere)
	uint8 MaxNodeNum;

	UFUNCTION(BlueprintCallable)
	FDungeonNode MakeNewNode(uint8 NodeNum, uint8 AssignedMapID,  ENodeType NodeType, FVector2D UICoordinate);
	
	UFUNCTION(BlueprintCallable)
	void ConnectNodesByDistance(float MaxDistance, int MaxEdgePerNode);

	UFUNCTION(BlueprintCallable)
	void ConnectNodesByMST(float MaxDistance);

	UFUNCTION(BlueprintCallable)
	bool CheckHasRoute(uint8 CurrentNodeNum, uint8 DestNodeNum);

	UFUNCTION(BlueprintCallable)
	FVector2D GetCubicBezier(float t, const FVector2D Point);
	
	UFUNCTION(BlueprintCallable)
	FVector2D GetQuadBezier(float t, const FVector2D StartPoint, const FVector2D EndPoint, const FVector2D ControlPoint);

	
	
};
