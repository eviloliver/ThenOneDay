// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_InstantSkill.h"

#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

UMJGA_InstantSkill::UMJGA_InstantSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UMJGA_InstantSkill::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if (!ASC)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist ASC"));
		return false;
	}

	const UMJCharacterAttributeSet* CharacterAttributeSet = ASC->GetSet<UMJCharacterAttributeSet>();
	const UMJCharacterSkillAttributeSet* SkillAttributeSet = ASC->GetSet<UMJCharacterSkillAttributeSet>();

	if (CharacterAttributeSet && SkillAttributeSet)
	{
		// TODO: 더 좋은 방법이 있을거 같음
		if (SkillAttributeSet->GetCostMana() > 0 && CharacterAttributeSet->GetMana() < SkillAttributeSet->GetCostMana())
		{
			MJ_LOG(LogMJ, Warning, TEXT("Need Mana"));

			return false;
		}
		if (SkillAttributeSet->GetCostStamina() > 0 && CharacterAttributeSet->GetStamina() < SkillAttributeSet->GetCostStamina())
		{
			MJ_LOG(LogMJ, Warning, TEXT("Need Stamina"));

			return false;
		}
		if (SkillAttributeSet->GetCostFocus() > 0 && CharacterAttributeSet->GetFocus() < SkillAttributeSet->GetCostFocus())
		{
			MJ_LOG(LogMJ, Warning, TEXT("Need Focus"));
			return false;
		}
	}

	if (ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.Cooldown"))))
	{
		MJ_LOG(LogMJ, Warning, TEXT("Instant Cooldown"));
		return false;
	}

	return true;
}

void UMJGA_InstantSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ApplyCost(Handle, ActorInfo, ActivationInfo);

	ApplyCooldown(Handle, ActorInfo, ActivationInfo);
}


void UMJGA_InstantSkill::ApplyCost(const FGameplayAbilitySpecHandle Handle,
                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (!CostGameplayEffectClass)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist CostGameplayEffect"));
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

	FGameplayEffectSpecHandle CostSpecHandle = MakeOutgoingGameplayEffectSpec(CostGameplayEffectClass, 1.0f);
	if (!CostSpecHandle.Data)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist CostSpecHandle.Data"));
		return;
	}

	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostStamina")), SkillAttributeSet->GetCostStamina() * -1.f);
	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostMana")), SkillAttributeSet->GetCostMana() * -1.f);
	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostFocus")), SkillAttributeSet->GetCostFocus() * -1.f);

	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, CostSpecHandle);
}

void UMJGA_InstantSkill::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
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