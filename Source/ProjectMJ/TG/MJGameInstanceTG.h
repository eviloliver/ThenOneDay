// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJDungeonStruct.h"
#include "Engine/GameInstance.h"
#include "MJGameInstanceTG.generated.h"


class AMJPlayerCharacter;
class UMJHttpDownloadManager;
class UMJSaveGame;
/**
 * Class Description: 게임 시작부터 종료까지 유지될 GameInstance
 * Author: 차태관
 * Created Date: 2025-06-11
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-11
 */
UCLASS()
class PROJECTMJ_API UMJGameInstanceTG : public UGameInstance
{
	GENERATED_BODY()
public:
	UMJGameInstanceTG();

	virtual void Init() override;
	
	TObjectPtr<UMJHttpDownloadManager> HttpDownloader;

	
	
	// SaveGame Section
	
	UFUNCTION(BlueprintCallable)
	UMJSaveGame* GetSaveGameData();

	UFUNCTION(BlueprintCallable)
	void CreateSaveGame();
	
	UFUNCTION(BlueprintCallable)
	void LoadSaveGame(AMJPlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	void SaveGameToSlot(AMJPlayerCharacter* Player);
	
	UFUNCTION(BlueprintCallable)
	FVector GetSavedDummyPos();

	UFUNCTION(BlueprintCallable)
	void SetSavedDummyPos(FVector Input);

	UFUNCTION(BlueprintCallable)
	void SetSavedMapNodeNum(uint8 Input);

	UFUNCTION(BlueprintCallable)
	uint8 GetSavedMapNodeNum();


	UFUNCTION(BlueprintCallable)
	const FDungeonGraph& GetDungeonGraph() const { return DungeonGraph; }
	
protected:

	// GeneratingDungeonSystem Section

	UPROPERTY(BlueprintReadOnly )
	FDungeonGraph DungeonGraph;
	
	UFUNCTION(BlueprintCallable)
	bool GenerateDungeonGraph();

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
	
	UPROPERTY(VisibleAnywhere)
	FVector SavedDummyPos;

	UPROPERTY(VisibleAnywhere)
	uint8 SavedMapNodeNum;
	
	UPROPERTY(VisibleAnywhere)
	uint8 MaxNodeNum;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMJSaveGame> SaveGameData;
	
	
	const FString SaveSlotName = TEXT("DefaultSaveGameSlot");
	const int32 UserIndex = 0;
	
};
