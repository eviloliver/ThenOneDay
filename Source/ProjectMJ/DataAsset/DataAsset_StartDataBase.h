// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerType/MJPlayerStructType.h"
#include "DataAsset_StartDataBase.generated.h"

class UMJGA_GameplayAbility;
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
	TArray<TSubclassOf<UMJGA_GameplayAbility>>ActivateOnGivenAbility;

	UPROPERTY(EditDefaultsOnly, Category="Stat")
	TArray<TSubclassOf<UMJGA_GameplayAbility>>ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UMJGA_GameplayAbility>>& InAbilitesToGive, UMJAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
