// ThenOneDayStudio


#include "AbilitySystem/Effect/MJEC_MovementSpeedModifier.h"

#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"

struct FMJEC_MovementSpeedModifierStatics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(MovementSpeed)

    FMJEC_MovementSpeedModifierStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, MovementSpeed, Target, false)
    }
};

static const FMJEC_MovementSpeedModifierStatics& MovementSpeedModifierStatics()
{
    static FMJEC_MovementSpeedModifierStatics Statics;
    return Statics;
}

UMJEC_MovementSpeedModifier::UMJEC_MovementSpeedModifier()
{
    RelevantAttributesToCapture.Add(MovementSpeedModifierStatics().MovementSpeedDef);
}

void UMJEC_MovementSpeedModifier::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;

    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    float SlowPercent = 0.0f;
    SlowPercent = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Data.Skill.StatusEffectSlowPercent"), true, SlowPercent);
    if (SlowPercent != 0.f)
    {
        float NewSpeedMult = FMath::Clamp(1.f - SlowPercent * 0.01f, 0.f, 1.f);
        OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMJCharacterAttributeSet::GetMovementSpeedAttribute(), EGameplayModOp::Multiplicitive, NewSpeedMult));
    }
}
