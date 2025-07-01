// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJFocusTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MJFocusTarget::UBTTask_MJFocusTarget()
{
	NodeName = TEXT("FocusTarget");
}

EBTNodeResult::Type UBTTask_MJFocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner();
	if (OwnerController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (Target == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	OwnerController->SetFocus(Target);
	
	return EBTNodeResult::Succeeded;
}
