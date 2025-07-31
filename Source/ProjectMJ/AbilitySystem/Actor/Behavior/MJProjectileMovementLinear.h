// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Actor/Behavior/MJProjectileMovementBehaviorBase.h"
#include "MJProjectileMovementLinear.generated.h"

/**
 * Class Description: 투사체 직선 이동
 * Author: 신동민
 * Created Date: 2025.07.31
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

class AMJProjectileBase;

UCLASS()
class PROJECTMJ_API UMJProjectileMovementLinear : public UMJProjectileMovementBehaviorBase
{
	GENERATED_BODY()
	
public:
	UMJProjectileMovementLinear();

public:
	virtual void InitMovement(AMJProjectileBase* InProjectile) override;
	virtual void Move(AMJProjectileBase* InProjectile, float DeltaSeconds) override;
	
protected:
	UPROPERTY()
	TObjectPtr<AMJProjectileBase> OwnerProjectile;
};
