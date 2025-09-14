// ThenOneDayStudio


#include "AbilitySystem/Effect/MJEC_DamageOverTime.h"

#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"

struct FMJEC_DamageOverTimeStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health)

	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbilityPower)

	FMJEC_DamageOverTimeStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, Health, Target, false)

		DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, AttackDamage, Source, true)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, AbilityPower, Source, true)
	}
};

static const FMJEC_DamageOverTimeStatics& DamageOverTimeStatics()
{
	static FMJEC_DamageOverTimeStatics Statics;
	return Statics;
}

UMJEC_DamageOverTime::UMJEC_DamageOverTime()
{
	RelevantAttributesToCapture.Add(DamageOverTimeStatics().HealthDef);

	RelevantAttributesToCapture.Add(DamageOverTimeStatics().AttackDamageDef);
	RelevantAttributesToCapture.Add(DamageOverTimeStatics().AbilityPowerDef);
}

void UMJEC_DamageOverTime::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float SourceAttackDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageOverTimeStatics().AttackDamageDef, EvaluationParameters, SourceAttackDamage);

	float SourceAbilityPower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageOverTimeStatics().AbilityPowerDef, EvaluationParameters, SourceAbilityPower);


	float BaseDamage = 0.0f;
	BaseDamage = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusBaseDamage")), false, BaseDamage);

	float AttackDamageScaling = 0.0f;
	AttackDamageScaling = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectADScaling")), false, AttackDamageScaling);

	float AbilityPowerScaling = 0.0f;
	AbilityPowerScaling = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectAPScaling")), false, AbilityPowerScaling);

	float TickDamage = BaseDamage + (SourceAttackDamage * AttackDamageScaling) + (SourceAbilityPower * AbilityPowerScaling);


	int32 StackCount = Spec.GetStackCount();
	if (StackCount > 1)
	{
		TickDamage *= StackCount;
	}

	if (TickDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMJCharacterAttributeSet::GetHealthAttribute(), EGameplayModOp::Additive, -TickDamage));
	}
}
