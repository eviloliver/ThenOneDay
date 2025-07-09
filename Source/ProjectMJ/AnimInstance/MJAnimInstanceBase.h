// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MJAnimInstanceBase.generated.h"

class AMJPlayerCharacter;
class UCharacterMovementComponent;
/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 2025_06_12
 * Last Modified By: Lee JuHyeon
 * Last Modified Date: Add Class
 */
UCLASS()
class PROJECTMJ_API UMJAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;


public:
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="AnimData|LocomotionData")
	TObjectPtr<AMJPlayerCharacter> OwningCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	TObjectPtr<UCharacterMovementComponent> OwningCharacterMovementComponent;


	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category="Animation|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Animation|LocomotionData")
	bool bHasAcceleration;
};
