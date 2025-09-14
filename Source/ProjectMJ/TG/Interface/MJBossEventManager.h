// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MJBossEventManager.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMJBossEventManager : public UInterface
{
	GENERATED_BODY()
};

/*
 * Class Description: Interface which Handle Event
 * Author: Cha Tae Gwan
 * Created Date: 2025-06-30
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-06-30
 */
class PROJECTMJ_API IMJBossEventManager
{
	GENERATED_BODY()

public:
	
	virtual void PublishOnBossSpawned() = 0;

};
