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

	return true;
}

void UMJGA_InstantSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// UGameplayAbility::ActivateAbility의 주석에 있음 - 동민 -
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		MJ_LOG(LogMJ, Warning, TEXT("CommitAbility is false"));
		constexpr bool bReplicateEndAbility = true;
		constexpr bool bWasCancelled = true;
		EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
}

void UMJGA_InstantSkill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

bool UMJGA_InstantSkill::CalculateFinalCosts(const FGameplayAbilitySpecHandle Handle,
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

bool UMJGA_InstantSkill::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	// 원본 무시
	// 우린 비용이 미리 정해지지 않은 방식을 사용하기 때문에 - 동민 -

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


void UMJGA_InstantSkill::ApplyCost(const FGameplayAbilitySpecHandle Handle,
                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
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

void UMJGA_InstantSkill::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
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