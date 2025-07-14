// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FMJInputActionConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="Input"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;

	bool IsVaild() const;

};

/**
 * Class Description: Config_Data
 * Author: Lee JuHyeon
 * Created Date: 2025_06_14
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */

UCLASS()
class PROJECTMJ_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext>DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> DialogueMappingContext;
	
	UPROPERTY(EditDefaultsOnly, meta = (TitleProperty = InputTag))
	TArray<FMJInputActionConfig> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, meta = (TitleProperty = InputTag))
	TArray<FMJInputActionConfig>AbilityInputAction;

public:
	UInputMappingContext* GetDefaultMappingContext() const { return DefaultMappingContext.Get(); }
	UInputMappingContext* GetDialogueMappingContext() const { return DialogueMappingContext.Get(); }

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
	UInputAction* FindAbilityInputActionByTag(const FGameplayTag& InInputTag) const;
};
