// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
	UMJProjectileExplodeReaction();

	virtual void InitReaction(AMJProjectileBase* InProjectile) override;
	virtual void OnProjectileReact(AMJProjectileBase* InProjectile, AActor* HitActor, const FHitResult& Hit) override;

protected:
	void Explode();

public:
	UPROPERTY()
	TObjectPtr<AMJProjectileBase> OwnerProjectile;

	UPROPERTY(EditAnywhere, Category = "GameplayCue", meta = (Categories = "GameplayCue"))
	FGameplayTag GameplayCueTag;
};
