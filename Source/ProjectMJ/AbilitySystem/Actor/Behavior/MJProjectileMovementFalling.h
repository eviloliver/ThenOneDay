// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Actor/Behavior/MJProjectileMovementBehaviorBase.h"
#include "MJProjectileMovementFalling.generated.h"

/**
 * Class Description: 하늘에서 떨어지는 투사체
 * Author: 신동민
 * Created Date: 2025.08.02
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJProjectileMovementFalling : public UMJProjectileMovementBehaviorBase
{
	GENERATED_BODY()

public:
	UMJProjectileMovementFalling();

	virtual FTransform CalculateSpawnTransform(UGameplayAbility* OwningAbility, const FVector& TargetLocation, FName SpawnSocketName) override;
	virtual void InitMovement(AMJProjectileBase* InProjectile) override;
	virtual void Move(AMJProjectileBase* InProjectile, float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<AMJProjectileBase> OwnerProjectile;

	UPROPERTY()
	FVector MoveDirection;

};
