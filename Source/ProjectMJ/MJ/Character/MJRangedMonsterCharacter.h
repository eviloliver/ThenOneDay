// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "MJRangedMonsterCharacter.generated.h"

/**
 * Class Description: 원거리 몬스터
 * Author: Kim Minjin
 * Created Date: 2025.06.29.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API AMJRangedMonsterCharacter : public AMJMonsterCharacter
{
	GENERATED_BODY()

public:
	AMJRangedMonsterCharacter();

protected:
	virtual float GetAIMaximumAttackRange() override;
	virtual float GetAIMinimumAttackRange() override;

	virtual void AttackByAI() override;
	virtual void MeleeAttackByAI() override;
	virtual void RangeAttackByAI() override;
};
