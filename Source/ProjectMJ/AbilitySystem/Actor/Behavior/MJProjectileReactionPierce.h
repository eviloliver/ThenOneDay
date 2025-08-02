// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Actor/Behavior/MJProjectileReactionBehaviorBase.h"
#include "MJProjectileReactionPierce.generated.h"

/**
 * Class Description: 관통 여부
 * Author: 신동민
 * Created Date: 2025.08.02
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

UCLASS()
class PROJECTMJ_API UMJProjectileReactionPierce : public UMJProjectileReactionBehaviorBase
{
	GENERATED_BODY()

public:
	UMJProjectileReactionPierce();

	virtual void InitReaction(AMJProjectileBase* Projectile) override;
	virtual void OnProjectileReact(AMJProjectileBase* Projectile, AActor* HitActor, const FHitResult& Hit) override;

protected:
	UPROPERTY()
	TObjectPtr<AMJProjectileBase> OwnerProjectile;

	UPROPERTY()
	int32 RemainingPierceCount = 0;
};
