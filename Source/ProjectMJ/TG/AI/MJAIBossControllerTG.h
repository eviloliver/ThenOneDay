// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TG/AI/MJAIControllerBaseTG.h"
#include "MJAIBossControllerTG.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API AMJAIBossControllerTG : public AMJAIControllerBaseTG
{
	GENERATED_BODY()

public:
	AMJAIBossControllerTG();

protected:

	virtual void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;
	
	
};
