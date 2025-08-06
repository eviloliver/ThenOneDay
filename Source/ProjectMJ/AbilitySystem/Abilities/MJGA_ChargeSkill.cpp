// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_ChargeSkill.h"

#include "ProjectMJ.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

UMJGA_ChargeSkill::UMJGA_ChargeSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	MinChargeTime = 0.3f;
	bIsCharging = false;
	CurrentChargeTime = 0.0f;
}

bool UMJGA_ChargeSkill::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void UMJGA_ChargeSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);\

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		MJ_LOG(LogMJ, Warning, TEXT("CommitAbility is false"));
		constexpr bool bReplicateEndAbility = true;
		constexpr bool bWasCancelled = true;
		EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}

	BeginCharging();
}

void UMJGA_ChargeSkill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMJGA_ChargeSkill::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

bool UMJGA_ChargeSkill::CalculateFinalCosts(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, FSkillCost& OutCost) const
{
	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if (!ASC)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist ASC"));
		return false;
	}

	const UMJCharacterSkillAttributeSet* SkillAttributeSet = ASC->GetSet<UMJCharacterSkillAttributeSet>();
	if (!SkillAttributeSet)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist SkillAttributeSet"));
		return false;
	}

	OutCost.StaminaCost = SkillAttributeSet->GetCostStamina();
	OutCost.ManaCost = SkillAttributeSet->GetCostMana();

	// TODO: Focus는 현재 Focus 량을 다 소비하는 메커니즘이라 다르게 해야함 - 동민 -
	OutCost.FocusCost = SkillAttributeSet->GetCostFocus();

	return true;
}

bool UMJGA_ChargeSkill::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	FSkillCost FinalCost;
	if (!CalculateFinalCosts(Handle, ActorInfo, FinalCost))
	{
		MJ_LOG(LogMJ, Warning, TEXT("CalculateFinalCosts is false"));
		return false;
	}

	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if (!ASC)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist ASC"));
		return false;
	}

	const UMJCharacterAttributeSet* CharacterAttributeSet = ASC->GetSet<UMJCharacterAttributeSet>();
	if (!CharacterAttributeSet)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist CharacterAttributeSet"));
		return false;
	}

	if (CharacterAttributeSet->GetStamina() < FinalCost.StaminaCost)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Need Stamina"));
		return false;
	}

	if (CharacterAttributeSet->GetMana() < FinalCost.ManaCost)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Need Mana"));
		return false;
	}

	if (CharacterAttributeSet->GetFocus() < FinalCost.FocusCost)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Need Focus"));
		return false;
	}

	return true;
}

void UMJGA_ChargeSkill::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{
	MJ_LOG(LogMJ, Warning, TEXT("ApplyCost"));

	if (!CostGameplayEffectClass)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist CostGameplayEffect"));
		return;
	}

	FSkillCost FinalCost;
	if (!CalculateFinalCosts(Handle, ActorInfo, FinalCost))
	{
		MJ_LOG(LogMJ, Warning, TEXT("CalculateFinalCosts is false"));
		return;
	}

	FGameplayEffectSpecHandle CostSpecHandle = MakeOutgoingGameplayEffectSpec(CostGameplayEffectClass, 1.0f);
	if (!CostSpecHandle.Data)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist CostSpecHandle.Data"));
		return;
	}

	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostStamina")), FinalCost.StaminaCost * -1.f);
	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostMana")), FinalCost.ManaCost * -1.f);
	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostFocus")), FinalCost.FocusCost * -1.f);

	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, CostSpecHandle);
}

void UMJGA_ChargeSkill::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	if (!CooldownGameplayEffectClass)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist CooldownGameplayEffectClass"));
		return;
	}
	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if (!ASC)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist ASC"));
		return;
	}

	const UMJCharacterSkillAttributeSet* SkillAttributeSet = ASC->GetSet<UMJCharacterSkillAttributeSet>();
	if (!SkillAttributeSet)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist SkillAttributeSet"));
		return;
	}

	const UMJCharacterAttributeSet* CharacterAttributeSet = ASC->GetSet<UMJCharacterAttributeSet>();

	float BaseCooldown = SkillAttributeSet->GetCooldown();
	float CharacterSkillCooldown = CharacterAttributeSet->GetSkillCooldown() * 0.01f;
	float FinalCooldown = BaseCooldown * (100.f / (100.f + CharacterSkillCooldown));

	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(CooldownGameplayEffectClass, 1.f, ASC->MakeEffectContext());
	if (SpecHandle.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.Cooldown")), FinalCooldown);

		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
	return;
}

void UMJGA_ChargeSkill::BeginCharging()
{
	bIsCharging = true;
	CurrentChargeTime = 0.0f;

}

void UMJGA_ChargeSkill::EndCharging(bool bWasCancelled)
{
	bIsCharging = false;

	if (bWasCancelled)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

