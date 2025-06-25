// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Struct/MJDungeonSessionDataStruct.h"
#include "Struct/MJPlayerSessionDataStruct.h"
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
	
	UFUNCTION(BlueprintCallable)
	FMJPlayerSessionData& GetPlayerSessionDataRef();

	UFUNCTION(BlueprintCallable)
	TArray<FMJDungeonSessionData>& GetDungeonSessionDataRef();

protected:

	UPROPERTY(VisibleAnywhere)
	FMJPlayerSessionData PlayerSessionData;

	UPROPERTY(VisibleAnywhere)
	TArray<FMJDungeonSessionData> DungeonSessionData;
	
};
