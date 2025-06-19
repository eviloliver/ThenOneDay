// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/DataAsset_StartDataBase.h"
#include "GameplayTagContainer.h"
#include "DA_PlayerStartData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerAbilitySet
{
	GENERATED_BODY()

public:
	
	UPROPERTY( EditDefaultsOnly,BlueprintReadOnly,meta=(Categories="InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UMJGameplayAbility>AbilityToGrant;

	bool IsValid() const;
};



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
