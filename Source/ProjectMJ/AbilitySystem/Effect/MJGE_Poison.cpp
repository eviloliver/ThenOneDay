// ThenOneDayStudio


#include "AbilitySystem/Effect/MJGE_Poison.h"

#include "MJEC_DamageOverTime.h"

UMJGE_Poison::UMJGE_Poison()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;

	FGameplayEffectExecutionDefinition ExecutionDefinition;
	ExecutionDefinition.CalculationClass = UMJEC_DamageOverTime::StaticClass();

	Executions.Add(ExecutionDefinition);

    FSetByCallerFloat DurationCaller;
    DurationCaller.DataTag = FGameplayTag::RequestGameplayTag("Data.Skill.StatusEffectDuration");
    DurationMagnitude = FGameplayEffectModifierMagnitude(DurationCaller);

	// Period 도 SetByCaller로 넣을 수 있나
	Period = 1.0f;

	StackLimitCount = 9;
	StackingType = EGameplayEffectStackingType::AggregateBySource;
	StackDurationRefreshPolicy = EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication;
	StackPeriodResetPolicy = EGameplayEffectStackingPeriodPolicy::NeverReset;
}
