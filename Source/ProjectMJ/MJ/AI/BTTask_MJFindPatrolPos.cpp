// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJFindPatrolPos.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

UBTTask_MJFindPatrolPos::UBTTask_MJFindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_MJFindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* ControlledPawn = AIController->GetPawn();
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControlledPawn->GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	UAIPerceptionComponent* PerceptionComp = AIController->GetAIPerceptionComponent();
	if (PerceptionComp == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	FAISenseID SightSenseID = UAISense::GetSenseID<UAISense_Sight>();
	UAISenseConfig_Sight* SightConfig = Cast<UAISenseConfig_Sight>(PerceptionComp->GetSenseConfig(SightSenseID));
	if (SightConfig == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	float PatrolRadius = SightConfig->SightRadius;
	
	FNavLocation NextPatrolPos;
	FVector Origin = ControlledPawn->GetActorLocation();
	
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("PatrolPos", NextPatrolPos.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
