// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJChargeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJChargeAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
