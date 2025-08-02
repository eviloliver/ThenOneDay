// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileMovementLinear.h"

#include "ProjectMJ.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "Character/MJCharacterBase.h"

UMJProjectileMovementLinear::UMJProjectileMovementLinear()
{
}

FTransform UMJProjectileMovementLinear::CalculateSpawnTransform(UGameplayAbility* OwningAbility,
	const FVector& TargetLocation, FName SpawnSocketName)
{
	if (!OwningAbility)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwningAbility"));
		return FTransform::Identity;
	}

	AMJCharacterBase* ProjectileSpawner = Cast<AMJCharacterBase>(OwningAbility->GetAvatarActorFromActorInfo());

	FVector SpawnLocation = FVector::ZeroVector;
	USkeletalMeshComponent* CharacterMesh = ProjectileSpawner->GetMesh();
	if (SpawnSocketName != NAME_None && CharacterMesh && CharacterMesh->DoesSocketExist(SpawnSocketName))
	{
		SpawnLocation = CharacterMesh->GetSocketLocation(SpawnSocketName);
	}
	else
	{
		SpawnLocation = ProjectileSpawner->GetActorLocation() + ProjectileSpawner->GetActorForwardVector() * 100.0f;
	}
	const FRotator SpawnRotation = (TargetLocation - SpawnLocation).Rotation();

	return FTransform(SpawnRotation, SpawnLocation);
}

void UMJProjectileMovementLinear::InitMovement(AMJProjectileBase* InProjectile)
{
	OwnerProjectile = InProjectile;
	if (OwnerProjectile)
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
