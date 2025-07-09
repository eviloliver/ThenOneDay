// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "MJGC_ProjectileHit.generated.h"

/**
 * Class Description: Has Projectile Hit VFX Gameplay Cue
 * Author: 신동민
 * Created Date: 2025.07.09
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */

class UNiagaraSystem;

UCLASS()
class PROJECTMJ_API UMJGC_ProjectileHit : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:
	UMJGC_ProjectileHit();

	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayCue")
	TObjectPtr<UNiagaraSystem> NiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayCue")
	float Scale = 1.0f;

};
