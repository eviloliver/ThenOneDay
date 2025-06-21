// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJTurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJTurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJTurnToTarget();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
