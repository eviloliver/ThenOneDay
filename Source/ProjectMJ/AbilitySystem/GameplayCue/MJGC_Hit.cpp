// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayCue/MJGC_Hit.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

UMJGC_Hit::UMJGC_Hit()
{
}

bool UMJGC_Hit::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	if (!MyTarget)
	{
		return false;
	}
	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();
	if (HitResult)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(MyTarget, NiagaraSystem, HitResult->ImpactPoint , FRotator::ZeroRotator, FVector(Scale), true, true, ENCPoolMethod::AutoRelease);
	}
	else
	{
		for (const auto& TargetActor : Parameters.EffectContext.Get()->GetActors())
		{
			if (TargetActor.Get())
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(MyTarget, NiagaraSystem, TargetActor.Get()->GetActorLocation(), FRotator::ZeroRotator, FVector(Scale), true, true, ENCPoolMethod::AutoRelease);
			}
		}
	}

	return false;
}
