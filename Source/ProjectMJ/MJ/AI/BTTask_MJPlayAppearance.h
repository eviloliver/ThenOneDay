// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_PlayAnimation.h"
#include "BTTask_MJPlayAppearance.generated.h"

/**
 * Class Description: 맵에 몬스터 모습 등장
 * Author: Kim Minjin
 * Created Date: 2025.07.08.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJPlayAppearance : public UBTTask_PlayAnimation
{
	GENERATED_BODY()
public:
	UBTTask_MJPlayAppearance();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
