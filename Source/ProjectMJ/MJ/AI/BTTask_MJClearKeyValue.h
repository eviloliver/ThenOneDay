// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MJClearKeyValue.generated.h"

/**
 * Class Description: 설정된 BBKey의 값을 Clear
 * Author: Kim Minjin
 * Created Date: 2025.06.19.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJClearKeyValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MJClearKeyValue();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
