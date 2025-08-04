// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileMovementGravityFall.h"

#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"

UMJProjectileMovementGravityFall::UMJProjectileMovementGravityFall()
{
}

void UMJProjectileMovementGravityFall::Move(AMJProjectileBase* InProjectile, float DeltaSeconds)
{
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	FVector Gravity = FVector(0.0f, 0.0f, GetWorld()->GetGravityZ());
	Velocity += Gravity * DeltaSeconds;

	FVector NewLocation = OwnerProjectile->GetActorLocation() + Velocity * DeltaSeconds;
	OwnerProjectile->SetActorLocation(NewLocation, true);
}
