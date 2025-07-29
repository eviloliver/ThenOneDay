// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileExplodeReaction.h"

#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "Kismet/GameplayStatics.h"

auto UMJProjectileExplodeReaction::OnProjectileReact(AMJProjectileBase* Projectile, AActor* HitActor,
                                                     const FHitResult& Hit) -> void
{
	Super::OnProjectileReact(Projectile, HitActor, Hit);

    //if (!Projectile)
    //{
    //    return;

    //}

    //FVector ExplosionCenter = Projectile->GetActorLocation();


    //TArray<AActor*> OverlappedActors;
    //UGameplayStatics::GetAllActorsOfClass(Projectile->GetWorld(), AActor::StaticClass(), OverlappedActors);

    //for (AActor* OtherActor : OverlappedActors)
    //{
    //    if (!OtherActor || OtherActor == Projectile)
    //    {
    //        continue;
    //    }

    //    float Distance = FVector::Dist(OtherActor->GetActorLocation(), ExplosionCenter);
    //    if (Distance > 100.0f)
    //    {
    //        continue;
    //    }

    //}

    //// TODO: VFX

    //Projectile->Destroy();

}
