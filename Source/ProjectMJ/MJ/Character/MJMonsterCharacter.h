// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MJCharacterBase.h"
#include "MJ/Interface/MJCharacterAIInterface.h"
#include "MJMonsterCharacter.generated.h"

/**
 * Class Description: AICharacter
 * Author: Kim Minjin
 * Created Date: 2025.06.21.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API AMJMonsterCharacter : public AMJCharacterBase, public IMJCharacterAIInterface
{
	GENERATED_BODY()

public:
	AMJMonsterCharacter();

	// Interface
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAITurnSpeed() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAISight_SightRadius() override;
	virtual float GetAISight_LoseSightRadius() override;
	virtual float GetAISight_PeripheralVisionAngleDegrees() override;

	virtual void AttackByAI() override;
};
