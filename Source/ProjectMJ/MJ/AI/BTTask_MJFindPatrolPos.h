// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJFindPatrolPos.generated.h"

/**
 * Class Description: BBKey인 PatrolPos 설정 
 * Author: Kim Minjin
 * Created Date: 2025.06.19.
 * Last Modified By: Kim Minjin
 * Last Modified Date: (2025.08.10.) Sight Perception 기반으로 Patrol Radius 설정
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
