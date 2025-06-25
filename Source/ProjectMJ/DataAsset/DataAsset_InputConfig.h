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

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta=(Categories="InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;

	bool IsVaild()const;

	
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

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext>DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta=(TitleProperty=InputAction))
	TArray<FMJInputActionConfig> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = InputAction))
	TArray<FMJInputActionConfig>AbilityInputAction;


	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
};
