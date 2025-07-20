// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Struct/MJDungeonSessionDataStruct.h"
#include "Struct/MJPlayerSessionDataStruct.h"
#include "MJGameInstanceTG.generated.h"


class UMJAnimMontageDataAsset;
class UMJProjectileDataAsset;
class AMJPlayerCharacter;
class UMJHttpDownloadManager;
class UMJSaveGame;
class UDataTable;
/**
 * Class Description: 게임 시작부터 종료까지 유지될 GameInstance
 * Author: 차태관
 * Created Date: 2025-06-11
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-11
 * Modified Date: 2025.07.04
 * Modified By: 신동민
 * Modified Description: 전역에서 접근할 DataAsset 생성
 */
UCLASS()
class PROJECTMJ_API UMJGameInstanceTG : public UGameInstance
{
	GENERATED_BODY()
public:
	UMJGameInstanceTG();

	virtual void Init() override;
	virtual void OnStart() override;
	
	TObjectPtr<UMJHttpDownloadManager> HttpDownloader;

	bool bIsPlayerStateDirty = false;
	
	
	UFUNCTION(BlueprintCallable)
	FMJPlayerSessionData& GetPlayerSessionDataRef();

	UFUNCTION(BlueprintCallable)
	TArray<FMJDungeonSessionData>& GetDungeonSessionDataRef();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> SkillDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UDataTable> EnemyDataTable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMJProjectileDataAsset> ProjectileDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMJAnimMontageDataAsset> AnimMontageDataAsset;

protected:

	UPROPERTY(VisibleAnywhere)
	FMJPlayerSessionData PlayerSessionData;

	UPROPERTY(VisibleAnywhere)
	TArray<FMJDungeonSessionData> DungeonSessionData;
	
};
