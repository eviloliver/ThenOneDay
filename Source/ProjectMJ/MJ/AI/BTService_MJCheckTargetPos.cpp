// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTService_MJCheckTargetPos.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_MJCheckTargetPos::UBTService_MJCheckTargetPos()
{
	NodeName = TEXT("CheckTargetPos");
	Interval = 0.5f;
}

void UBTService_MJCheckTargetPos::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 블랙보드에서 타겟 가져와서 위치 키 업데이트
	/*
	 * TODO
	 * 감각을 바탕으로 업데이트하면 좋을 것 같음.
	 */
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("LastKnownPos", Target->GetTargetLocation());
}
