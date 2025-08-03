// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Actor/Behavior/MJProjectileMovementFalling.h"
#include "MJProjectileMovementFallingGravity.generated.h"

/**
 * Class Description: 하늘에서 떨어지는 투사체 (중력 적용)
 * Author: 신동민
 * Created Date: 2025.08.04
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJProjectileMovementFallingGravity : public UMJProjectileMovementFalling
{
	GENERATED_BODY()

public:
	UMJProjectileMovementFallingGravity();

	virtual void Move(AMJProjectileBase* InProjectile, float DeltaSeconds) override;
protected:

};
