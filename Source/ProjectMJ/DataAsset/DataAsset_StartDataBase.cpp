// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_StartDataBase.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"


void UDataAsset_StartDataBase::GiveToAbilitySystemComponent(UMJAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);
	GrantAbilities(ActivateOnGivenAbility, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

}

void UDataAsset_StartDataBase::GrantAbilities(const TArray<TSubclassOf<UMJGA_GameplayAbility>>& InAbilitesToGive, UMJAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UMJGA_GameplayAbility>Ability : InAbilitesToGive)
	{
		if (!Ability)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
		
	}
}
