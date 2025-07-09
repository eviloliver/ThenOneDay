// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJAttack.generated.h"

/**
 * Class Description: 공격
 * Author: Kim Minjin
 * Created Date: 2025.06.23.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
