// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGameplayAbility.h"
#include "MJDamageGameplayAbility.generated.h"

/**
 * Class Description: 데미지를 주는 어빌리티
 * Author: 신동민
 * Created Date: 2025_06_18
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UMJDamageGameplayAbility : public UMJGameplayAbility
{
	GENERATED_BODY()
	
public:
	UMJDamageGameplayAbility();

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);


protected:
	

};
