// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_MJCheckAttackRange.generated.h"

/**
 * Class Description: ServiceNode-타겟이 공격범위에 들어와 있는지 확인(근거리, 원거리)
 * Author: Kim Minjin
 * Created Date: 2025.06.25.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTService_MJCheckAttackRange : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_MJCheckAttackRange();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
