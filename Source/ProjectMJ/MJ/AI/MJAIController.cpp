// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/MJAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMJAIController::AMJAIController()
{
	/*
	 * TODO
	 * AIPerception 추가
	 */
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_MJMonster.BB_MJMonster'"));
	if (nullptr!=BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_MJMonster.BT_MJMonster'"));
	if (nullptr!= BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AMJAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		// 시작 위치 값 설정
		Blackboard->SetValueAsVector("HomePos", GetPawn()->GetActorLocation());
		
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AMJAIController::StopAI()
{
	/*
	 * TODO
	 * Character가 죽을 때 호출해야 됨
	 */
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AMJAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
