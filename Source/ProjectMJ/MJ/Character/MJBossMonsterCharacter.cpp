// ThenOneDayStudio


#include "MJ/Character/MJBossMonsterCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "MJ/AI/MJMonsterAIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"

void AMJBossMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	bHasTriggerPatten = false;
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetHealthAttribute()).AddUObject(this, &AMJBossMonsterCharacter::OnHealthChanged);
}

void AMJBossMonsterCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	float CurrentHp = Data.NewValue;
	bool bIsAttack = (CurrentHp / GetAttributeSet()->GetMaxHealth() <= 0.6);

	if (!bHasTriggerPatten && bIsAttack)
	{
		bHasTriggerPatten = true;

		AMJMonsterAIControllerBase* AIController = Cast<AMJMonsterAIControllerBase>(GetController());
		if (!AIController)
		{
			return;
		}
		UBlackboardComponent* BB = AIController->GetBlackboardComponent();
		if (!BB)
		{
			return;
		}

		BB->SetValueAsBool("IsAttack", bIsAttack);
	}
}
