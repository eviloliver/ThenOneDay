// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJ/AI/MJMonsterAIControllerBase.h"
#include "MJMeleeMonsterAIController.generated.h"

/**
 * Class Description: MonsterAIController-베이스상속
 * Author: Kim Minjin
 * Created Date: 2025.06.21.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API AMJMeleeMonsterAIController : public AMJMonsterAIControllerBase
{
	GENERATED_BODY()

public:
	AMJMeleeMonsterAIController();

	virtual void BeginPlay() override;
};
