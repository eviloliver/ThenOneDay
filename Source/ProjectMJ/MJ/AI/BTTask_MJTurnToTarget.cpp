// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJTurnToTarget.h"

#include "AIController.h"
#include "ProjectMJ.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MJ/Interface/MJCharacterAIInterface.h"

UBTTask_MJTurnToTarget::UBTTask_MJTurnToTarget()
{
	NodeName = TEXT("Turn");

	TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTTask_MJTurnToTarget::OnRotated);
}

EBTNodeResult::Type UBTTask_MJTurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// reset timer handle
	// TimerHandle.Invalidate();
	MyOwnerComp = &OwnerComp;

	AAIController* Controller = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (Controller == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* ControlledPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (nullptr == TargetPawn)
	{
		return EBTNodeResult::Failed;
	}
	
	FVector LookVector = TargetPawn->GetActorLocation() - ControlledPawn->GetActorLocation();
	LookVector.Z = 0.0f;
	TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	Controller->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, GetWorld()->GetDeltaSeconds(), /*bLoop=*/true);
	
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_MJTurnToTarget::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const Controller = OwnerComp.GetAIOwner();

	if (Controller && TimerHandle.IsValid())
	{
		Controller->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
	TimerHandle.Invalidate();
	
	return EBTNodeResult::Aborted;
}

void UBTTask_MJTurnToTarget::OnRotated()
{
	AAIController* Controller = Cast<AAIController>(MyOwnerComp->GetOwner());
	if (Controller == nullptr)
	{
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Failed);
	}

	APawn* ControlledPawn = Cast<APawn>(Controller->GetPawn());
	if (ControlledPawn == nullptr)
	{
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Failed);
	}

	IMJCharacterAIInterface* AIPawn = Cast<IMJCharacterAIInterface>(ControlledPawn);
	if (nullptr == AIPawn)
	{
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Failed);
	}

	/*
	 * Minjin
	 * TurnSpeed는 5.0f 이상이 좋아보입니다.
	 */
	float TurnSpeed = AIPawn->GetAITurnSpeed();
	FRotator NewRot = FMath::RInterpTo(ControlledPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), TurnSpeed);
	ControlledPawn->SetActorRotation(NewRot);

	float AngleDiff = FMath::Abs((NewRot - TargetRot).GetNormalized().Yaw);
	
	if (AngleDiff < 1.0f)
	{
		MJ_LOG(LogMJ,Log, TEXT("회전완료"));
		// we're done here, report success so that BT can pick next task
		ControlledPawn->GetWorldTimerManager().ClearTimer(TimerHandle);
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
}
