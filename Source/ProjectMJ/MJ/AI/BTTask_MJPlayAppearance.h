// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_PlayAnimation.h"
#include "BTTask_MJPlayAppearance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJPlayAppearance : public UBTTask_PlayAnimation
{
	GENERATED_BODY()
public:
	UBTTask_MJPlayAppearance();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
