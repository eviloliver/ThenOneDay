// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJFindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJFindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJFindPatrolPos();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
