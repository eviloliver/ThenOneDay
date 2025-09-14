// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
    for (const FMJInputActionConfig& InputActionConfig : NativeInputActions)
    {
        if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
        {
            return InputActionConfig.InputAction;
        }
    }
    return nullptr;
}

UInputAction* UDataAsset_InputConfig::FindAbilityInputActionByTag(const FGameplayTag& InInputTag) const
{
    for (const FMJInputActionConfig& InputActionConfig : AbilityInputActions)
    {
        if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
        {
            return InputActionConfig.InputAction;
        }
    }
    return nullptr;
}

bool FMJInputActionConfig::IsVaild() const
{
    return InputTag.IsValid() && InputAction;
}
