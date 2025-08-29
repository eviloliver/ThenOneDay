// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJNormalAttack.generated.h"

/**
 * Class Description: Normal Attack
 * Author: Kim Minjin
 * Created Date: 2025.07.15.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJNormalAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJNormalAttack();

protected:
	FDelegateHandle Handle;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
};
