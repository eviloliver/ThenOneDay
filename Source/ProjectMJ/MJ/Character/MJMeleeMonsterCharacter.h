// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "MJMeleeMonsterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API AMJMeleeMonsterCharacter : public AMJMonsterCharacter
{
	GENERATED_BODY()

public:
	AMJMeleeMonsterCharacter();

protected:

	virtual void BeginPlay() override;
};
