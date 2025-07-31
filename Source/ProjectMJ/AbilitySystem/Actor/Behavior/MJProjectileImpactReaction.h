// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Actor/Behavior/MJProjectileReactionBehaviorBase.h"
#include "MJProjectileImpactReaction.generated.h"

/**
 * Class Description: 기본적인 충돌
 * Author: 신동민
 * Created Date: 2025.07.31
 * Description of Change:
 * Modified By:
 * Modified Date:
 */


UCLASS()
class PROJECTMJ_API UMJProjectileImpactReaction : public UMJProjectileReactionBehaviorBase
{
	GENERATED_BODY()

public:
	UMJProjectileImpactReaction();

public:
	virtual void InitReaction(AMJProjectileBase* Projectile) override;
	virtual void OnProjectileReact(AMJProjectileBase* Projectile, AActor* HitActor, const FHitResult& Hit) override;

protected:
	UPROPERTY()
	TObjectPtr<AMJProjectileBase> OwnerProjectile;
};
