// ThenOneDayStudio


#include "MJ/AI/BTTask_MJAppear.h"

#include "AIController.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/MJCharacterBase.h"

UBTTask_MJAppear::UBTTask_MJAppear()
{
}

EBTNodeResult::Type UBTTask_MJAppear::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ControlledPawn->SetActorHiddenInGame(false);
	ControlledPawn->SetActorEnableCollision(true);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsAppear", true);

	AMJCharacterBase* Character = Cast<AMJCharacterBase>(ControlledPawn);
	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Character.Appear"));
	Character->ASC->HandleGameplayEvent(EventData.EventTag, &EventData);

	return EBTNodeResult::Succeeded;
}
