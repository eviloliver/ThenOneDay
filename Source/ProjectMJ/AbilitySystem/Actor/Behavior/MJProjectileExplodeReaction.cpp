// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileExplodeReaction.h"

#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "Kismet/GameplayStatics.h"

auto UMJProjectileExplodeReaction::OnProjectileReact(AMJProjectileBase* Projectile, AActor* HitActor,
                                                     const FHitResult& Hit) -> void
{
	Super::OnProjectileReact(Projectile, HitActor, Hit);

}

void UMJProjectileExplodeReaction::InitReaction(AMJProjectileBase* Projectile)
{
	Super::InitReaction(Projectile);
}
