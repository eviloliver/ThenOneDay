// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Actor/Behavior/MJProjectileReactionBehaviorBase.h"
#include "MJProjectileExplodeReaction.generated.h"

/**
 * Class Description: 투사체 폭발
 * Author: 신동민
 * Created Date: 2025.07.29
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

UCLASS()
class PROJECTMJ_API UMJProjectileExplodeReaction : public UMJProjectileReactionBehaviorBase
{
	GENERATED_BODY()
public:
	virtual void OnProjectileReact(AMJProjectileBase* Projectile, AActor* HitActor, const FHitResult& Hit) override;
	virtual void InitReaction(AMJProjectileBase* Projectile) override;
};
