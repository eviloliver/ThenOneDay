// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/MJAnimInstanceBase.h"
#include "MJPlayerLinkAnimLayer.generated.h"

class UMJPlayerAnimInstance;
/**
 * Class Description: Using GameplayTag change Anime for WeaponType
 * Author: Lee JuHyeon
 * Created Date: 2025_06_21
 * Last Modified By: Lee JuHyeon
 * Last Modified Date: Add Get Func
 */
UCLASS()
class PROJECTMJ_API UMJPlayerLinkAnimLayer : public UMJAnimInstanceBase
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UMJPlayerAnimInstance* GetPlayerAnimInstance() const;

};
