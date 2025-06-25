// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PlayerType/MJPlayerStructType.h"
#include "MJAbilitySystemComponent.generated.h"

class AMJPlayerCharacter;
/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 2025_06_12
 * Last Modified By:Add RemoveAbilityFunc
 * Last Modified Date: 2025_06_23
 */
UCLASS()
class PROJECTMJ_API UMJAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	// What for ? 
public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);

	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category="Player|Ability", meta=(ApplyLevel="1"))
	void GrantHeroWeaponAbilities(const TArray< FPlayerAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "Player|Ability")
	void RemovedGrantedPlayerWeaponAbilies(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToMove);

};
