// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "MJStoneElementCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API AMJStoneElementCharacter : public AMJMonsterCharacter
{
	GENERATED_BODY()

public:
	AMJStoneElementCharacter();

protected:
	virtual void BeginPlay() override;
};
