// ThenOneDayStudio


#include "AbilitySystem/Effect/MJGE_SkillCost.h"

#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"

UMJGE_SkillCost::UMJGE_SkillCost()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// TODO:  결국 스킬 유형마다로 변경해야할 듯
	// 지금은 그냥 안 쓰는 자원을 0 으로 받는 중

	FGameplayModifierInfo StaminaModifier;
	StaminaModifier.Attribute = UMJCharacterAttributeSet::GetStaminaAttribute();
	StaminaModifier.ModifierOp = EGameplayModOp::Additive;
	FSetByCallerFloat SetByCallerStamina;
	SetByCallerStamina.DataTag = FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostStamina"));
	StaminaModifier.ModifierMagnitude = SetByCallerStamina;
	Modifiers.Add(StaminaModifier);

	FGameplayModifierInfo ManaModifier;
	ManaModifier.Attribute = UMJCharacterAttributeSet::GetManaAttribute();
	ManaModifier.ModifierOp = EGameplayModOp::Additive;
	FSetByCallerFloat SetByCallerMana;
	SetByCallerMana.DataTag = FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostMana"));
	ManaModifier.ModifierMagnitude = SetByCallerMana;
	Modifiers.Add(ManaModifier);

	FGameplayModifierInfo FocusModifier;
	FocusModifier.Attribute = UMJCharacterAttributeSet::GetFocusAttribute();
	FocusModifier.ModifierOp = EGameplayModOp::Additive;
	FSetByCallerFloat SetByCallerFocus;
	SetByCallerFocus.DataTag = FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostFocus"));
	FocusModifier.ModifierMagnitude = SetByCallerFocus;
	Modifiers.Add(FocusModifier);
}
