// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJTurnToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MJ/Interface/MJCharacterAIInterface.h"

UBTTask_MJTurnToTarget::UBTTask_MJTurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_MJTurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControlledPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (nullptr == TargetPawn)
	{
		return EBTNodeResult::Failed;
	}

	IMJCharacterAIInterface* AIPawn = Cast<IMJCharacterAIInterface>(ControlledPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}
	
	float TurnSpeed = AIPawn->GetAITurnSpeed();
	FVector LookVector = TargetPawn->GetActorLocation() - ControlledPawn->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	ControlledPawn->SetActorRotation(FMath::RInterpTo(ControlledPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), TurnSpeed));

	return EBTNodeResult::Succeeded;
}
