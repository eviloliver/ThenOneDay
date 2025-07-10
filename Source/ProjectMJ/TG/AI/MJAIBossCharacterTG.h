// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "MJAIBossCharacterTG.generated.h"

/**
 * Class Description: Boss AI Chracter class 
 * Author: Cha Tae Gwan
 * Created Date: 2025-06-28
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-06-28
 */
UCLASS()
class PROJECTMJ_API AMJAIBossCharacterTG : public AMJMonsterCharacter
{
	GENERATED_BODY()

public:
	AMJAIBossCharacterTG();

protected:

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	
	
};
