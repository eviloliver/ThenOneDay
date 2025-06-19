// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DA_PlayerStartData.h"
#include "AbilitySystem/Abilities/MJGameplayAbility.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
bool FPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UDA_PlayerStartData::GiveToAbilitySystemComponent(UMJAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FPlayerAbilitySet& AbilitySet : PlayerStartAbilitySets)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
		UE_LOG(LogTemp, Warning, TEXT("Point"));
	}
}
