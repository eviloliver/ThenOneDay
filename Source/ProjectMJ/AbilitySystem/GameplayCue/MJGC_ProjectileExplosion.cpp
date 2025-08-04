// ThenOneDayStudio


#include "AbilitySystem/GameplayCue/MJGC_ProjectileExplosion.h"

#include "NiagaraFunctionLibrary.h"
#include "ProjectMJ.h"

UMJGC_ProjectileExplosion::UMJGC_ProjectileExplosion()
{
}

bool UMJGC_ProjectileExplosion::OnExecute_Implementation(AActor* MyTarget,
	const FGameplayCueParameters& Parameters) const
{
	FVector SpawnLocation;

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
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				MyTarget->GetWorld(),
				ExplosionVFX,
				SpawnLocation,
				FRotator::ZeroRotator,
				FVector(Scale));
		}

	}

	// TODO:SFX
	return true;
}
