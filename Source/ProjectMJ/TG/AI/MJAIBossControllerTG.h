// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TG/AI/MJAIControllerBaseTG.h"
#include "MJAIBossControllerTG.generated.h"

/**
 * Class Description: Boss AI Controller class 
 * Author: Cha Tae Gwan
 * Created Date: 2025-06-28
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-06-28
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
