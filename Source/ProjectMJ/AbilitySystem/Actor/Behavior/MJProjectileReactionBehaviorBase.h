// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MJProjectileReactionBehaviorBase.generated.h"

class AMJProjectileBase;
/**
 * Class Description: 투사체 충돌 반응 로직
 * Author: 신동민
 * Created Date: 2025.07.29
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS(Abstract)
class PROJECTMJ_API UMJProjectileReactionBehaviorBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnProjectileReact(AMJProjectileBase* Projectile, AActor* HitActor, const FHitResult& Hit) PURE_VIRTUAL(UMJProjectileReactionBehaviorBase::OnProjectileReact, );
	virtual void InitReaction(AMJProjectileBase* Projectile) PURE_VIRTUAL(UMJProjectileReactionBehaviorBase::InitReaction, );
	
};
