// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJKeepDistanceWhileMoveTo.generated.h"

/**
 * Class Description: 타겟과 거리를 유지하며 이동
 * Author: Kim Minjin
 * Created Date: 2025.07.01.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJKeepDistanceWhileMoveTo : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJKeepDistanceWhileMoveTo();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
