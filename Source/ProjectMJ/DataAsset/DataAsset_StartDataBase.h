// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartDataBase.generated.h"

class UMJGameplayAbility;
class UMJAbilitySystemComponent;
/**
 * Class Description: Character Stat Data
 * Author: Lee JuHyeon
 * Created Date: 2025_06_14
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UDataAsset_StartDataBase : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UMJAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:

	UPROPERTY(EditDefaultsOnly, Category="Stat")
	TArray<TSubclassOf<UMJGameplayAbility>>ActivateOnGivenAbility;

	UPROPERTY(EditDefaultsOnly, Category="Stat")
	TArray<TSubclassOf<UMJGameplayAbility>>ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UMJGameplayAbility>>& InAbilitesToGive, UMJAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
