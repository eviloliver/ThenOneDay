// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJPlayAppearance.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MJPlayAppearance::UBTTask_MJPlayAppearance()
{
	NodeName = TEXT("Appear With Anim");
}

EBTNodeResult::Type UBTTask_MJPlayAppearance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ControlledPawn->SetActorHiddenInGame(false);
	ControlledPawn->SetActorEnableCollision(true);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsAppear", true);

	AMJMonsterCharacter* Character = Cast<AMJMonsterCharacter>(ControlledPawn);
	if (ControlledPawn)
	{
		if (Character->GetAppearanceAnimation())
		{
			AnimationToPlay = Character->GetAppearanceAnimation();	
		}
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
