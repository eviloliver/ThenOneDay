﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "Character/MJPlayerCharacter.h"
// #include "Character/Component/MJSkillComponentBase.h"


//This is a function that detects key presses in GAS. 
void UMJAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);
	
	if (Spec.IsActive())
	{
		// Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
	}

}
//This is a function that detects key Release in GAS.
void UMJAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);

	//TArray<UGameplayAbility*> Instances = Spec.GetAbilityInstances();
	//const FGameplayAbilityActivationInfo& ActivationInfo = Instances.Last()->GetCurrentActivationInfoRef();
	//FPredictionKey OriginalPredictionKey = ActivationInfo.GetActivationPredictionKey();
	//InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, OriginalPredictionKey);

}

void UMJAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

}

void UMJAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			continue;
		}
		AbilitySpecInputReleased(AbilitySpec);
		
	}
}

void UMJAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FPlayerAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FPlayerAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level=ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UMJAbilitySystemComponent::RemovedGrantedPlayerWeaponAbilies(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToMove)
{
	if (InSpecHandlesToMove.IsEmpty())
	{
		return;
	}
	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToMove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}

	}
	InSpecHandlesToMove.Empty();
}
