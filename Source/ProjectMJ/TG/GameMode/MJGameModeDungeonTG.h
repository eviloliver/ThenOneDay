// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/MJGameModeBase.h"
#include "MJGameModeDungeonTG.generated.h"

/**
 * Class Description: Dungeon`s Gamemode
 * Author: 차태관
 * Created Date: 2025-06-14
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-14
 */
UCLASS()
class PROJECTMJ_API AMJGameModeDungeonTG : public AMJGameModeBase
{
	GENERATED_BODY()

public:
	AMJGameModeDungeonTG();
	
	virtual bool TravelToMapByNode(const FString MapName, const uint8 NodeNum) override;

protected:

	virtual void BeginPlay() override;

	
	

};
