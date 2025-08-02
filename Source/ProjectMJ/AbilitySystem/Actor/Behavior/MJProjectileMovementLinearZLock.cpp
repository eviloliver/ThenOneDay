// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileMovementLinearZLock.h"

#include "ProjectMJ.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "Character/MJCharacterBase.h"

UMJProjectileMovementLinearZLock::UMJProjectileMovementLinearZLock()
{
}

void UMJProjectileMovementLinearZLock::InitMovement(AMJProjectileBase* InProjectile)
{
	Super::InitMovement(InProjectile);
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

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

	FVector NewLocation = OwnerProjectile->GetActorLocation() + MoveDirection * MoveSpeed * DeltaSeconds;

	NewLocation.Z = InitialZLocation;

	OwnerProjectile->SetActorLocation(NewLocation, true);
}
