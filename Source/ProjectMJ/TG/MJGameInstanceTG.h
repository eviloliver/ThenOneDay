// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	// Getter 
	
	UFUNCTION(BlueprintCallable)
	FVector GetSavedDummyPos();

	UFUNCTION(BlueprintCallable)
	uint8 GetSavedMapNodeNum();
	
	
	// Setter
	
	UFUNCTION(BlueprintCallable)
	void SetSavedDummyPos(FVector Input);

	UFUNCTION(BlueprintCallable)
	void SetSavedMapNodeNum(uint8 Input);
	

protected:
	
	UPROPERTY(VisibleAnywhere)
	FVector SavedDummyPos;

	UPROPERTY(VisibleAnywhere)
	uint8 SavedMapNodeNum;
	
	
};
