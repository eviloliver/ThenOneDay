// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJProjectileMovementLinear.h"
#include "MJProjectileMovementLinearZLock.generated.h"

/**
 * Class Description: Z 좌표 고정 이동 전략
 * Author: 신동민
 * Created Date: 2025.08.02
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

UCLASS()
class PROJECTMJ_API UMJProjectileMovementLinearZLock : public UMJProjectileMovementLinear
{
	GENERATED_BODY()

public:
	UMJProjectileMovementLinearZLock();

	virtual void InitMovement(AMJProjectileBase* InProjectile) override;
	virtual void Move(AMJProjectileBase* InProjectile, float DeltaSeconds) override;

protected:

	UPROPERTY()
	float InitialZLocation;
};
