// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileReactionPierce.h"

UMJProjectileReactionPierce::UMJProjectileReactionPierce()
{
}

void UMJProjectileReactionPierce::InitReaction(AMJProjectileBase* Projectile)
{
	Super::InitReaction(Projectile);
}

void UMJProjectileReactionPierce::OnProjectileReact(AMJProjectileBase* Projectile, AActor* HitActor,
	const FHitResult& Hit)
{
	Super::OnProjectileReact(Projectile, HitActor, Hit);
}

