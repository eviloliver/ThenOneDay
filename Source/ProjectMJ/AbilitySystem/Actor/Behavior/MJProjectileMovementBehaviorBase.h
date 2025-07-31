// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MJProjectileMovementBehaviorBase.generated.h"

/**
 * Class Description: 투사체 이동 로직
 * Author: 신동민
 * Created Date: 2025.07.29
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

class AMJProjectileBase;

UCLASS()
class PROJECTMJ_API UMJProjectileMovementBehaviorBase : public UObject
{
	GENERATED_BODY()

public:

	virtual void InitMovement(AMJProjectileBase* InProjectile) PURE_VIRTUAL(UMJProjectileMovementBehaviorBase::InitMovement, );
	virtual void Move(AMJProjectileBase* InProjectile, float DeltaSeconds) PURE_VIRTUAL(UMJProjectileMovementBehaviorBase::Move, );

};
