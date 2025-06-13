// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTService_Detect.h"
#include "MJAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr != World)
	{
		return;
	}
	
	/*
	 * TODO
	 * DetectRadius 하드 코딩 고치기
	 */
	float DetectRadius = 400.0f;

	/*
	 * TODO
	 * 타겟 탐지
	 */
	
}
