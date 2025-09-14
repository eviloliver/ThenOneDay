// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJTurnToTarget.generated.h"

/**
 * Class Description: 타겟방향으로 회전시키는 노드
 * Author: Kim Minjin
 * Created Date: 2025.06.22.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJTurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJTurnToTarget();
	
protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> MyOwnerComp;
	
	FRotator TargetRot;
	
	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnRotated();
};
