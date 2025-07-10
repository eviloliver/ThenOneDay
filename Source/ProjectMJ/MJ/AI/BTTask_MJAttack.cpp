// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJAttack.h"
#include "AIController.h"
#include "Abilities/GameplayAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MJ/Interface/MJCharacterAIInterface.h"

UBTTask_MJAttack::UBTTask_MJAttack()
{
}

EBTNodeResult::Type UBTTask_MJAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
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

	AIPawn->AttackByAI();

	return EBTNodeResult::Succeeded;
}
