// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MJCharacterAIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMJCharacterAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Class Description: AICharacter Interface-Task, Perception 관련 데이터
 * Author: Kim Minjin
 * Created Date: 2025.06.22.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
class PROJECTMJ_API IMJCharacterAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetAIPatrolRadius() = 0;
	virtual float GetAITurnSpeed() = 0;
	virtual float GetAIAttackRange() = 0;
	virtual float GetAISight_SightRadius() = 0;
	virtual float GetAISight_LoseSightRadius() = 0;
	virtual float GetAISight_PeripheralVisionAngleDegrees() = 0;

	virtual void AttackByAI() = 0;
};
