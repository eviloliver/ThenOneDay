// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_MJCheckTargetPos.generated.h"

/**
 * Class Description: ServiceNode-타겟의 위치를 받아옴
 * Author: Kim Minjin
 * Created Date: 2025.06.19.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTService_MJCheckTargetPos : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_MJCheckTargetPos();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
