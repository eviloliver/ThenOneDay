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

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStringTable> MapNames;

	UPROPERTY(BlueprintReadOnly)
	FString CurrentMapName;
	
	UFUNCTION(BlueprintCallable)
	bool TravelToMap(const FString MapName);
	
	
};
