// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileMovementFalling.h"

#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"

UMJProjectileMovementFalling::UMJProjectileMovementFalling()
{
	MoveDirection = FVector(0.0f, 0.0f, -1.0f);
}

FTransform UMJProjectileMovementFalling::CalculateSpawnTransform(UGameplayAbility* OwningAbility,
	const FVector& TargetLocation, FName SpawnSocketName)
{
	return Super::CalculateSpawnTransform(OwningAbility, TargetLocation, SpawnSocketName);
}

void UMJProjectileMovementFalling::InitMovement(AMJProjectileBase* InProjectile)
{
	OwnerProjectile = InProjectile;
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist "))
	}

	//FVector SpawnLocation = TargetLocation;
	//SpawnLocation.Z += 3000.0f; // 하늘 위

	//const FRotator SpawnRotation = FRotator(-90.f, 0.f, 0.f); // 아래를 바라보는 방향

	//return FTransform(SpawnRotation, SpawnLocation);
}

void UMJProjectileMovementFalling::Move(AMJProjectileBase* InProjectile, float DeltaSeconds)
{
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	const float MoveSpeed = OwnerProjectile->ProjectileParams.ProjectileSpeed;
	FVector NewLocation = OwnerProjectile->GetActorLocation() + MoveDirection * MoveSpeed * DeltaSeconds;

	OwnerProjectile->SetActorLocation(NewLocation, true);
}
