// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_MJAttackInRange.generated.h"

/**
 * Class Description: 타겟이 공격범위에 들어왔는지 확인하는 데코레이터
 * Author: Kim Minjin
 * Created Date: 2025.06.23.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTDecorator_MJAttackInRange : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_MJAttackInRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
