// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayCue/MJGC_ProjectileHit.h"

#include "NiagaraFunctionLibrary.h"
#include "ProjectMJ.h"

UMJGC_ProjectileHit::UMJGC_ProjectileHit()
{
}

bool UMJGC_ProjectileHit::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	if (!MyTarget)
	{
		return false;
	}
	if (!NiagaraSystem)
	{
		return false;
	}

	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();

	if (HitResult)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(MyTarget, NiagaraSystem, HitResult->ImpactPoint, FRotator::ZeroRotator, FVector(Scale), true, true, ENCPoolMethod::AutoRelease);
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
