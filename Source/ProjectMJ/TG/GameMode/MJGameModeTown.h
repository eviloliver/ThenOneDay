// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/MJGameModeBase.h"
#include "MJGameModeTown.generated.h"

/**
 * Class Description: Town`s Gamemode
 * Author: 차태관
 * Created Date: 2025-06-11
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-11
 */
UCLASS()
class PROJECTMJ_API AMJGameModeTown : public AMJGameModeBase
{
	GENERATED_BODY()

public:
	AMJGameModeTown();

	virtual void BeginPlay() override;
	

protected:

	
	

	
	
};
