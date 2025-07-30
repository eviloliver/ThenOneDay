// ThenOneDayStudio


#include "AbilitySystem/Effect/MJGE_SkillCooldown.h"

UMJGE_SkillCooldown::UMJGE_SkillCooldown()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;

	FSetByCallerFloat SetByCallerCooldown;
	SetByCallerCooldown.DataTag = FGameplayTag::RequestGameplayTag(FName("Data.Skill.Cooldown"));
	DurationMagnitude = SetByCallerCooldown;
}
