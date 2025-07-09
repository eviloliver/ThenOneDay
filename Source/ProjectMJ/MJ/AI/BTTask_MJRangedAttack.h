// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJRangedAttack.generated.h"

/**
 * Class Description: 원거리공격 노드
 * Author: Kim Minjin
 * Created Date: 2025.07.01.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJRangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJRangedAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
