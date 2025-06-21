// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/MJAnimInstanceBase.h"
#include "MJPlayerLinkAnimLayer.generated.h"

class UMJPlayerAnimInstance;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJPlayerLinkAnimLayer : public UMJAnimInstanceBase
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UMJPlayerAnimInstance* GetPlayerAnimInstance() const;

};
