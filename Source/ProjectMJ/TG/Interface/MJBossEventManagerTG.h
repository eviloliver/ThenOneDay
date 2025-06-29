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

/**
 * 
 */
class PROJECTMJ_API IMJBossEventManagerTG
{
	GENERATED_BODY()

public:

	virtual void PublishOnBossHealthChanged(float Delta, float OldHealth, float NewHealth) = 0;

	virtual void PublishOnBossSpawned(float Health) = 0;

};
