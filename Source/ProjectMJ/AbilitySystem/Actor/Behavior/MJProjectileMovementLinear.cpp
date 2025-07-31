// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileMovementLinear.h"

#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"

UMJProjectileMovementLinear::UMJProjectileMovementLinear()
{
}

void UMJProjectileMovementLinear::InitMovement(AMJProjectileBase* InProjectile)
{
	OwnerProjectile = InProjectile;
}

void UMJProjectileMovementLinear::Move(AMJProjectileBase* InProjectile, float DeltaSeconds)
{
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	const float MoveSpeed = OwnerProjectile->ProjectileParams.ProjectileSpeed;
	const FVector NewLocation = OwnerProjectile->GetActorLocation() + OwnerProjectile->GetActorForwardVector() * MoveSpeed * DeltaSeconds;
	OwnerProjectile->SetActorLocation(NewLocation);
}
