// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTService_MJCheckAttackRange.h"

#include "AIController.h"
#include "ProjectMJ.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MJ/Interface/MJCharacterAIInterface.h"

UBTService_MJCheckAttackRange::UBTService_MJCheckAttackRange()
{
	NodeName = "CheckAttackRange";
	Interval = 0.1f;
}

void UBTService_MJCheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	/*
	 * How to: 타겟이 몬스터의 공격 범위에 들어갔을 때 Maximum 혹은 Minimum 범위에 들어오면 블랙보드 키를 설정
	 */
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControlledPawn == nullptr)
	{
		return;
	}

	IMJCharacterAIInterface* AIPawn = Cast<IMJCharacterAIInterface>(ControlledPawn);
	if (AIPawn == nullptr)
	{
		return;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (Target == nullptr)
	{
		return;
	}
	DrawDebugCircle(GetWorld(), ControlledPawn->GetActorLocation(), AIPawn->GetAIMaximumAttackRange(), 16, FColor::Emerald, false, 0.2f, 0, 0, FVector::RightVector,FVector::ForwardVector, false);
	DrawDebugCircle(GetWorld(), ControlledPawn->GetActorLocation(), AIPawn->GetAIMinimumAttackRange(), 16, FColor::Magenta, false, 0.2f, 0, 0, FVector::RightVector,FVector::ForwardVector, false);
	
	float DistanceTo = FVector::Distance(Target->GetActorLocation(), ControlledPawn->GetActorLocation());
	float DistanceToTarget = ControlledPawn->GetDistanceTo(Target);

	// Minjin: 원거리 범위에 속할 경우
	bool IsRange = DistanceToTarget <= AIPawn->GetAIMaximumAttackRange()
		&& DistanceToTarget > AIPawn->GetAIMinimumAttackRange();
	// Minjin: 근거리 범위에 속할 경우
	bool IsMelee = DistanceToTarget <= AIPawn->GetAIMinimumAttackRange();
	
	if (IsRange)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("MaximumAttackRange", true);
		OwnerComp.GetBlackboardComponent()->ClearValue("MinimumAttackRange");
	}
	else if (IsMelee)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("MinimumAttackRange", true);
		OwnerComp.GetBlackboardComponent()->ClearValue("MaximumAttackRange");
	}
	else
	{
		// Minjin: 아무 범위에도 안 속할 경우: 키 값 클리어
		OwnerComp.GetBlackboardComponent()->ClearValue("MinimumAttackRange");
		OwnerComp.GetBlackboardComponent()->ClearValue("MaximumAttackRange");
	}
	
	return;
}
