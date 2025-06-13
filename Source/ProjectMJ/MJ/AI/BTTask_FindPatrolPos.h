// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPatrolPos.generated.h"

/**
 * Class Description: Task-목표 지점 찾는 태스크
 * Author: Kim Minjin
 * Created Date: 2025.06.13.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_FindPatrolPos : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
