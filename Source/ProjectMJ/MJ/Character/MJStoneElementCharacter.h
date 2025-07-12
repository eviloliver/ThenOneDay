// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJ/Character/MJMeleeMonsterCharacter.h"
#include "MJStoneElementCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API AMJStoneElementCharacter : public AMJMeleeMonsterCharacter
{
	GENERATED_BODY()
public:

	AMJStoneElementCharacter() {};
	virtual void BeginPlay() override;

	virtual void AttackByAI() override;
};
