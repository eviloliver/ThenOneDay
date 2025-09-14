// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileMovementLinearZLock.h"

#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"

UMJProjectileMovementLinearZLock::UMJProjectileMovementLinearZLock()
{
}

void UMJProjectileMovementLinearZLock::InitMovement(AMJProjectileBase* InProjectile)
{
	Super::InitMovement(InProjectile);

	InitialZLocation = OwnerProjectile->GetActorLocation().Z;

}

void UMJProjectileMovementLinearZLock::Move(AMJProjectileBase* InProjectile, float DeltaSeconds)
{
	OwnerProjectile = InProjectile;
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	const float MoveSpeed = OwnerProjectile->ProjectileParams.ProjectileSpeed;

	FVector NewLocation = OwnerProjectile->GetActorLocation() + Velocity * DeltaSeconds;

	NewLocation.Z = InitialZLocation;

	OwnerProjectile->SetActorLocation(NewLocation, true);
}
