// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MJGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API AMJGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMJGameModeBase();

	


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> MapNames;
	
	UFUNCTION(BlueprintCallable)
	bool TravelToMapByNode(const FString MapName, const uint8 NodeNum);
	
	UFUNCTION(BlueprintCallable)
	bool TravelToMap(const FString MapName);
};
