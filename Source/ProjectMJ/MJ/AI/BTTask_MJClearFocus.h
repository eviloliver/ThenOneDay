// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJClearFocus.generated.h"

/**
 * Class Description: 타겟으로 고정한 시선을 해제
 * Author: Kim Minjin
 * Created Date: 2025.06.29.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJClearFocus : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJClearFocus();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
