// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/DataAsset_StartDataBase.h"
#include "GameplayTagContainer.h"
#include "DA_PlayerStartData.generated.h"

/**
 * Class Description: Character Stat Data
 * Author: Lee JuHyeon
 * Created Date: 2025_06_19
 * Last Modified By: Add Start Player Ability
 * Last Modified Date: 2025_06_19
 */




UCLASS()
class PROJECTMJ_API UDA_PlayerStartData : public UDataAsset_StartDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UMJAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartData", meta = (TitleProperty = "InputTag"))
	TArray<FPlayerAbilitySet> PlayerStartAbilitySets;

};
