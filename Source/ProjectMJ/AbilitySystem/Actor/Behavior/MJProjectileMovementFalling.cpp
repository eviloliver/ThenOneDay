// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileMovementFalling.h"

#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"

UMJProjectileMovementFalling::UMJProjectileMovementFalling()
{

}

FTransform UMJProjectileMovementFalling::CalculateSpawnTransform(UGameplayAbility* OwningAbility,
	const FVector& TargetLocation, FName SpawnSocketName)
{
	FVector SpawnLocation = TargetLocation;

	float SpawnHeightOffSet = 2000.0f;
	SpawnLocation.Z += SpawnHeightOffSet;

	const FRotator SpawnRotation = FRotator(-90.0f, 0.0f, 0.0f);

	return FTransform(SpawnRotation.Quaternion(), SpawnLocation);

}

void UMJProjectileMovementFalling::InitMovement(AMJProjectileBase* InProjectile)
{
	OwnerProjectile = InProjectile;
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}
	float MoveSpeed = OwnerProjectile->ProjectileParams.ProjectileSpeed;

	Velocity = OwnerProjectile->GetActorForwardVector() * MoveSpeed;
}

void UMJProjectileMovementFalling::Move(AMJProjectileBase* InProjectile, float DeltaSeconds)
{
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	//FVector Gravity = FVector(0.0f, 0.0f, GetWorld()->GetGravityZ());
	//Velocity += Gravity * DeltaSeconds;

	FVector NewLocation = OwnerProjectile->GetActorLocation() + Velocity * DeltaSeconds;
	OwnerProjectile->SetActorLocation(NewLocation, true);

}
