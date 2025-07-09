// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MJBossEventManagerTG.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMJBossEventManagerTG : public UInterface
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
class PROJECTMJ_API IMJBossEventManagerTG
{
	GENERATED_BODY()

public:

	virtual void PublishOnBossHealthChanged(float Delta) = 0;

	virtual void PublishOnBossSpawned(float Health) = 0;

};
