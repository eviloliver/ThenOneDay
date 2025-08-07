// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effect/MJEC_SkillDamage.h"

#include "ProjectMJ.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

// TODO: 지금은 주는 순수 데미지만 계산하는데, 버프 디버프 관련 공식은 빠져있다. + 난수도 빠져 있다
struct FMJEC_SkillDamageStatics
{

    DECLARE_ATTRIBUTE_CAPTUREDEF(Health)

    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDamage)
    DECLARE_ATTRIBUTE_CAPTUREDEF(AbilityPower)
    DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalChance)
    DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalDamage)

    FMJEC_SkillDamageStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, Health, Target, false)

        DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, AttackDamage, Source, true)
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, AbilityPower, Source, true)
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, CriticalChance, Source, true)
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMJCharacterAttributeSet, CriticalDamage, Source, true)
    }
};

static const FMJEC_SkillDamageStatics& DamageStatics()
{
    static FMJEC_SkillDamageStatics DStatics;
    return DStatics;
}

UMJEC_SkillDamage::UMJEC_SkillDamage()
{
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);

	RelevantAttributesToCapture.Add(DamageStatics().AttackDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().AbilityPowerDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalDamageDef);
}


void UMJEC_SkillDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;

    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    float SourceAttackDamage = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackDamageDef, EvaluationParameters, SourceAttackDamage);

    float SourceAbilityPower = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AbilityPowerDef, EvaluationParameters, SourceAbilityPower);

    float CriticalChance = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalChanceDef, EvaluationParameters, CriticalChance);

    float CriticalDamage = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalDamageDef, EvaluationParameters, CriticalDamage);


    float BaseDamage = 0.0f;
    BaseDamage = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.BaseDamage")), true, BaseDamage);
  
    float AttackDamageScaling = 0.0f;
    AttackDamageScaling = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AttackDamageScaling")), true, AttackDamageScaling);

    float AbilityPowerScaling = 0.0f;
    AbilityPowerScaling = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AbilityPowerScaling")), true, AbilityPowerScaling);

    float FinalDamage = BaseDamage + ((AttackDamageScaling / 100) * SourceAttackDamage) + ((AbilityPowerScaling / 100) * SourceAbilityPower);

    bool bIsCritical = FMath::FRandRange(0.f, 100.f) < CriticalChance;
    if (bIsCritical)
    {
	    FinalDamage *= (1.0f + CriticalDamage / 100.0f);
    	// TODO:크리티컬 연출/태그 등 처리

    	FGameplayTag IsCriticalTag = FGameplayTag::RequestGameplayTag(FName("Data.Character.IsCritical"));
    	ExecutionParams.GetOwningSpecForPreExecuteMod()->AddDynamicAssetTag(IsCriticalTag);
    }
    	
     // TODO: 난수 추가
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMJCharacterAttributeSet::GetHealthAttribute(), EGameplayModOp::Additive, -FinalDamage));

}