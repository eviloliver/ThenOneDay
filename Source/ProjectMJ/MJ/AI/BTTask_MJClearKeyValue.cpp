// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJClearKeyValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MJClearKeyValue::UBTTask_MJClearKeyValue()
{
	NodeName = TEXT("ClearKeyValue");
}

EBTNodeResult::Type UBTTask_MJClearKeyValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
	
	return EBTNodeResult::Succeeded;
}
