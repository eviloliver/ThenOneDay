// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTDecorator_MJAttackInRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MJ/Interface/MJCharacterAIInterface.h"

UBTDecorator_MJAttackInRange::UBTDecorator_MJAttackInRange()
{
}

bool UBTDecorator_MJAttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControlledPawn)
	{
		return false;
	}

	IMJCharacterAIInterface* AIPawn = Cast<IMJCharacterAIInterface>(ControlledPawn);
	if (nullptr == AIPawn)
	{
		return false;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (nullptr == Target)
	{
		return false;
	}

	float DistanceToTarget = ControlledPawn->GetDistanceTo(Target);
	float AttackRange = AIPawn->GetAIAttackRange();
	bResult = (DistanceToTarget <= AttackRange);

	UE_LOG(LogTemp, Log, TEXT("AttackInRange is %s"), bResult ? TEXT("true") : TEXT("false"));	
	return bResult;
}
