// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/MJGameModeBase.h"
#include "MJGameModeTG.generated.h"

/**
 * Class Description: TG`s Gamemode
 * Author: 차태관
 * Created Date: 2025-06-11
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-11
 */
UCLASS()
class PROJECTMJ_API AMJGameModeTG : public AMJGameModeBase
{
	GENERATED_BODY()

public:
	AMJGameModeTG();

	virtual void BeginPlay() override;
	

	UFUNCTION(BlueprintCallable)
	FString GetCurrentMapName();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStringTable> MapNames;

	UPROPERTY(BlueprintReadOnly)
	FString CurrentMapName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStringTable> DungeonNames;
	
	UFUNCTION(BlueprintCallable)
	bool TravelToMap(const FString MapName);
	
	void HandleTownLogic();

	void HandleeDungeonLogic();

	

	
	
};
