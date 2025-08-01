// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileMovementLinear.h"

#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"

UMJProjectileMovementLinear::UMJProjectileMovementLinear()
{
}

void UMJProjectileMovementLinear::InitMovement(AMJProjectileBase* InProjectile, const FTransform& SpawnTransform)
{
	OwnerProjectile = InProjectile;

	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	const FVector TargetLocation = OwnerProjectile->ProjectileParams.TargetLocation;
	if (TargetLocation != FVector::ZeroVector)
	{
		MoveDirection = (TargetLocation - OwnerProjectile->GetActorLocation()).GetSafeNormal();
	}
	else
	{
		MoveDirection = OwnerProjectile->GetActorForwardVector();
	}
}

void UMJProjectileMovementLinear::Move(AMJProjectileBase* InProjectile, float DeltaSeconds)
{
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	const float MoveSpeed = OwnerProjectile->ProjectileParams.ProjectileSpeed;
	const FVector NewLocation = OwnerProjectile->GetActorLocation() + MoveDirection * MoveSpeed * DeltaSeconds;
	OwnerProjectile->SetActorLocation(NewLocation);
}
