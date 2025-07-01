// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJKeepDistanceWhileMoveTo.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MJ/Interface/MJCharacterAIInterface.h"

UBTTask_MJKeepDistanceWhileMoveTo::UBTTask_MJKeepDistanceWhileMoveTo()
{
	NodeName = TEXT("KeepDistanceMove");
}

EBTNodeResult::Type UBTTask_MJKeepDistanceWhileMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner();
	if (OwnerController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* ControlledPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	IMJCharacterAIInterface* AIPawn = Cast<IMJCharacterAIInterface>(ControlledPawn);
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (TargetPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector AILocation = ControlledPawn->GetActorLocation();
	FVector TargetLocation = TargetPawn->GetActorLocation();
	float Distance = FVector::Dist(AILocation, TargetLocation);
	
	// Minjin: 거리가 MinimumAttackRange이하일 경우->플레이어와 멀어진다
	if (Distance <= AIPawn->GetAIMinimumAttackRange()||
		OwnerComp.GetBlackboardComponent()->GetValueAsBool("MinimumAttackRange"))
	{
		FVector AwayDir = (AILocation - TargetLocation).GetSafeNormal();
		FVector MoveToLocation = AILocation + AwayDir * (AIPawn->GetAIMaximumAttackRange() - Distance);

		OwnerController->MoveToLocation(MoveToLocation);
		return EBTNodeResult::Succeeded;
	}

	// Minjin: 거리가 MaximumAttackRange보다 멀 경우->플레이어와 가까워진다
	if (Distance > AIPawn->GetAIMaximumAttackRange()||
		!OwnerComp.GetBlackboardComponent()->GetValueAsBool("MaximumAttackRange"))
	{
		FVector ToDir = (TargetLocation - AILocation).GetSafeNormal();
		FVector MoveToLocation = AILocation + ToDir * (Distance - AIPawn->GetAIMaximumAttackRange());

		OwnerController->MoveToLocation(MoveToLocation);
		return EBTNodeResult::Succeeded;
	}

	// Minjin: Min~Max 범위에 있을 경우->제자리
	OwnerController->StopMovement();

	return EBTNodeResult::Succeeded;
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
