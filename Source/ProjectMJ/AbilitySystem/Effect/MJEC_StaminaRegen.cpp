// ThenOneDayStudio


#include "AbilitySystem/Effect/MJEC_StaminaRegen.h"

#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"

struct FMJEC_StaminaRegenStatics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(StaminaRegeneration);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Stamina);
    DECLARE_ATTRIBUTE_CAPTUREDEF(MaxStamina);

    FMJEC_StaminaRegenStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, StaminaRegeneration, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, Stamina, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, MaxStamina, Target, false);
    }
};
static FMJEC_StaminaRegenStatics& RegenStatics()
{
    static FMJEC_StaminaRegenStatics RStatics;
    return RStatics;
}

UMJEC_StaminaRegen::UMJEC_StaminaRegen()
{
    RelevantAttributesToCapture.Add(RegenStatics().StaminaRegenerationDef);
    RelevantAttributesToCapture.Add(RegenStatics().StaminaDef);
    RelevantAttributesToCapture.Add(RegenStatics().MaxStaminaDef);
}

void UMJEC_StaminaRegen::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;

    EvaluationParameters.SourceTags = SourceTags;

    float RegenPerSec = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(RegenStatics().StaminaRegenerationDef, FAggregatorEvaluateParameters(), RegenPerSec);

    float CurrentStamina = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(RegenStatics().StaminaDef, FAggregatorEvaluateParameters(), CurrentStamina);

    float MaxStamina = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(RegenStatics().MaxStaminaDef, FAggregatorEvaluateParameters(), MaxStamina);

    // TODO: 하드코딩 개선
    const float Period = 1.0f;

    // Attribute에서 Clamp 했지만 여기서도 처리하는게 좋음 - 동민 -
    const float Missing = FMath::Max(0.f, MaxStamina - CurrentStamina);
    const float Gain = FMath::Max(0.f, RegenPerSec) * Period;
    const float Final = FMath::Min(Gain, Missing);

    if (Final > 0.f)
    {
        OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMJCharacterAttributeSet::GetStaminaAttribute(), EGameplayModOp::Additive, Final));
    }
}
