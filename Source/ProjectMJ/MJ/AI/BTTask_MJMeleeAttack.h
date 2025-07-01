// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJMeleeAttack.generated.h"

/**
 * Class Description: 근거리공격 노드
 * Author: Kim Minjin
 * Created Date: 2025.07.01.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJMeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJMeleeAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
