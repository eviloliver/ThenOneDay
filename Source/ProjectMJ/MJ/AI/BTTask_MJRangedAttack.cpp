// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJRangedAttack.h"

#include "AIController.h"
#include "MJ/Interface/MJCharacterAIInterface.h"

UBTTask_MJRangedAttack::UBTTask_MJRangedAttack()
{
	NodeName = TEXT("RangedAttack");
}

EBTNodeResult::Type UBTTask_MJRangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	IMJCharacterAIInterface* AIPawn = Cast<IMJCharacterAIInterface>(ControlledPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	AIPawn->RangeAttackByAI();
	/*
	 * TODO
	 * 공격이 다 끝난 후에 완료 처리해야 한다.
	 */
	return EBTNodeResult::Succeeded;
}
