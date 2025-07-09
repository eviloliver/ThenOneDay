// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJFocusTarget.generated.h"

/**
 * Class Description: 시선을 타겟으로 고정
 * Author: Kim Minjin
 * Created Date: 2025.06.29.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJFocusTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJFocusTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
