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

	
	UFUNCTION(BlueprintCallable)
	FString GetCurrentMapName();


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> MapNames;

	UPROPERTY(BlueprintReadOnly)
	FString CurrentMapName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStringTable> DungeonNames;
	
	UFUNCTION(BlueprintCallable)
	bool TravelToMap(const FString MapName);
};
