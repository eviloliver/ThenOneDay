// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJKeepDistanceWhileMoveTo.h"

#include "AIController.h"
#include "NavigationSystem.h"
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
	
	// Minjin: 거리가 MinimumAttackRange 미만일 경우->플레이어와 멀어진다
	if (Distance < AIPawn->GetAIMinimumAttackRange()||
		OwnerComp.GetBlackboardComponent()->GetValueAsBool("MinimumAttackRange"))
	{
		FVector AwayDir = (AILocation - TargetLocation).GetSafeNormal();
		FVector RandomDir = FMath::VRandCone(AwayDir, FMath::DegreesToRadians(30.f));
		FVector MoveToLocation = AILocation + RandomDir *(AIPawn->GetAIMaximumAttackRange() - Distance);

		// FNavLocation Destination;
		//
		// UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControlledPawn->GetWorld());
		// if (nullptr == NavSystem)
		// {
		// 	return EBTNodeResult::Failed;
		// }
		// // TODO 최소 이상 혹은 원거리 범위로 이동하도록 만들기 -> EQS_RandomPosInDonut
		//
		// NavSystem->GetRandomPointInNavigableRadius(AwayDir, AIPawn->GetAIMaximumAttackRange() * 1.5f , Destination);
		// OwnerController->MoveToLocation(Destination);
		
		OwnerController->MoveToLocation(MoveToLocation);
	
		return EBTNodeResult::Succeeded;
	}

	// Minjin: 거리가 MaximumAttackRange보다 멀 경우->플레이어와 가까워진다
	if (Distance > AIPawn->GetAIMaximumAttackRange()||
		!OwnerComp.GetBlackboardComponent()->GetValueAsBool("MaximumAttackRange"))
	{
		FVector ToDir = (TargetLocation - AILocation).GetSafeNormal();
		FVector RandomDir = FMath::VRandCone(ToDir, FMath::DegreesToRadians(30.f));
		
		FVector MoveToLocation = AILocation + RandomDir * (Distance - AIPawn->GetAIMaximumAttackRange());

		// Minjin: AcceptanceRadius 0.0f로 설정-> 정확히 목표지점에 와야 도착으로 간주
		OwnerController->MoveToLocation(MoveToLocation, 0.0f, false);
		
		return EBTNodeResult::Succeeded;
	}

	// Minjin: Min~Max 범위에 있을 경우->제자리
	OwnerController->StopMovement();

	return EBTNodeResult::Succeeded;
}
