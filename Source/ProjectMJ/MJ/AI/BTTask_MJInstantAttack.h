// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJInstantAttack.generated.h"

/**
 * Class Description: Instant Attack
 * Author: Kim Minjin
 * Created Date: 2025.07.15.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJInstantAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJInstantAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
