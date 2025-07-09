// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "MJGC_Hit.generated.h"

class UNiagaraSystem;
/**
 * Class Description: Has Hit VFX Gameplay Cue
 * Author: 신동민
 * Created Date: 2025_06_18
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */

UCLASS()
class PROJECTMJ_API UMJGC_Hit : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
public:
	UMJGC_Hit();

	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayCue")
	TObjectPtr<UNiagaraSystem> NiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayCue")
	float Scale = 1.0f;
};
