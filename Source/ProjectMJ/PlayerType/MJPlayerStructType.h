// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MJPlayerStructType.generated.h"

class UMJPlayerLinkAnimLayer;
class UMJGameplayAbility;
class UInputMappingContext;

/**
 * Class Description: Ability related class 
 * Author: Lee JuHyeon
 * Created Date: 2025_06_20
 * Last Modified By: Add Weapon Data and IMC
 * Last Modified Date: 2025_06_23
 */

USTRUCT(BlueprintType)
struct FPlayerAbilitySet
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UMJGameplayAbility>AbilityToGrant;

	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FMJPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UMJPlayerLinkAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta=(TitleProperty="InputTag"))
	TArray< FPlayerAbilitySet>DefaultWeaponAbilities;

};

