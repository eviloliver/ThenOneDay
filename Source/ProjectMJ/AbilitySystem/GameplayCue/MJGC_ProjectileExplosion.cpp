// ThenOneDayStudio


#include "AbilitySystem/GameplayCue/MJGC_ProjectileExplosion.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"

UMJGC_ProjectileExplosion::UMJGC_ProjectileExplosion()
{
}

bool UMJGC_ProjectileExplosion::OnExecute_Implementation(AActor* MyTarget,
	const FGameplayCueParameters& Parameters) const
{
	FVector SpawnLocation;
	float ExplosionRadius = Parameters.RawMagnitude;

	if (!Parameters.Location.IsNearlyZero())
	{
		SpawnLocation = Parameters.Location;
	}
	else if (MyTarget)
	{
		SpawnLocation = MyTarget->GetActorLocation();
	}
	else
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist MyTarget"));
	}

	if (ExplosionVFX)
	{
		if (MyTarget)
		{
			UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				MyTarget->GetWorld(),
				ExplosionVFX,
				SpawnLocation,
				FRotator::ZeroRotator,
				FVector(1.0f));

			{
				float NiagaraScale = ExplosionRadius / EffectRatio;
				NiagaraComponent->SetFloatParameter(TEXT("Scale_All"), NiagaraScale);
			}
		}
	}

	// TODO:SFX
	return true;
}
