// ThenOneDayStudio


#include "MJ/AI/BTService_MJCheckHealth.h"
#include "BTService_MJCheckHealth.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/MJForestCreatureCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"


UBTService_MJCheckHealth::UBTService_MJCheckHealth()
{
	NodeName = TEXT("CheckHealth");
	Interval = 0.1f;
}


void UBTService_MJCheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	ControlledPawn =Cast<AMJForestCreatureCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!ControlledPawn)
	{
		return;
	}
	Blackboard = OwnerComp.GetBlackboardComponent();

	CachedASC = ControlledPawn->GetAbilitySystemComponent();
	if (!CachedASC)
	{
		return;
	}

	CachedASC->GetGameplayAttributeValueChangeDelegate(ControlledPawn->GetAttributeSet()->GetHealthAttribute()).AddUObject(this, &UBTService_MJCheckHealth::EnemyOnChangedHealth);

}

void UBTService_MJCheckHealth::EnemyOnChangedHealth(const FOnAttributeChangeData& Data)
{
	if (!Blackboard)
	{
		return;
	}
	float CurrentHP = Data.NewValue;
	bool IsSet = (CurrentHP <= 200.f) ? true : false;
	
	Blackboard->SetValueAsBool("IsAttack",IsSet);
}