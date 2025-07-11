// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MJAnimInstanceBase.generated.h"

class AMJCharacterBase;
class UCharacterMovementComponent;
/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 2025_06_12
 * Last Modified By: Kim Minjin
 * Last Modified Date: (25.07.10.)Change Cast
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
	TObjectPtr<AMJCharacterBase> OwningCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	TObjectPtr<UCharacterMovementComponent> OwningCharacterMovementComponent;


	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category="Animation|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Animation|LocomotionData")
	bool bHasAcceleration;
};
