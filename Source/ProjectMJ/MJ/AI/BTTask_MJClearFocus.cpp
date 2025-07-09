// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJClearFocus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MJClearFocus::UBTTask_MJClearFocus()
{
	NodeName = TEXT("ClearFocus");
}

EBTNodeResult::Type UBTTask_MJClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
	
	return EBTNodeResult::Succeeded;
}
