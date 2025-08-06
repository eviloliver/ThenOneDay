// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileMovementFall.h"

#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"

UMJProjectileMovementFall::UMJProjectileMovementFall()
{

}

FTransform UMJProjectileMovementFall::CalculateSpawnTransform(UGameplayAbility* OwningAbility,
	const FVector& TargetLocation, FName SpawnSocketName)
{
	FVector SpawnLocation = TargetLocation;

	SpawnLocation.Z += SpawnHeightOffset;

	const FRotator SpawnRotation = FRotator(-90.0f, 0.0f, 0.0f);

	return FTransform(SpawnRotation.Quaternion(), SpawnLocation);

}

void UMJProjectileMovementFall::InitMovement(AMJProjectileBase* InProjectile)
{
	OwnerProjectile = InProjectile;
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	TimeSinceSpawn = 0.0f;

	float MoveSpeed = OwnerProjectile->ProjectileParams.ProjectileSpeed;

	Velocity = OwnerProjectile->GetActorForwardVector() * MoveSpeed;
}

void UMJProjectileMovementFall::Move(AMJProjectileBase* InProjectile, float DeltaSeconds)
{
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	TimeSinceSpawn += DeltaSeconds;

	if (TimeSinceSpawn < DelayTime)
	{
		OwnerProjectile->SetActorLocation(OwnerProjectile->GetActorLocation());
		return;
	}

	FVector NewLocation = OwnerProjectile->GetActorLocation() + Velocity * DeltaSeconds;
	OwnerProjectile->SetActorLocation(NewLocation, true);

}
