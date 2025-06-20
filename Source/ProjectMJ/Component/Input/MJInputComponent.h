// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "MJInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject,class CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
	
	template<class UserObject, class CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* COntextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleaseFunc);
};

template<class UserObject, class CallbackFunc>
inline void UMJInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template<class UserObject, class CallbackFunc>
inline void UMJInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* COntextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleaseFunc)
{
	checkf(InInputConfig, TEXT("Input config data aseet is Null, can not Proceed with binding"));
	
	for (const FMJInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputAction)
	{
		if (!AbilityInputActionConfig.IsVaild())
		{
			continue;
		}
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, COntextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, COntextObject, InputReleaseFunc, AbilityInputActionConfig.InputTag);
	}

}
