// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileReactionPierce.h"

UMJProjectileReactionPierce::UMJProjectileReactionPierce()
{
}

void UMJProjectileReactionPierce::InitReaction(AMJProjectileBase* InProjectile)
{
	Super::InitReaction(InProjectile);
}

void UMJProjectileReactionPierce::OnProjectileReact(AMJProjectileBase* InProjectile, AActor* HitActor,
	const FHitResult& Hit)
{
	Super::OnProjectileReact(InProjectile, HitActor, Hit);
}

