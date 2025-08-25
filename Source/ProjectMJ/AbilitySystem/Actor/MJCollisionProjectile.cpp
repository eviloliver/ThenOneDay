// ThenOneDayStudio


#include "AbilitySystem/Actor/MJCollisionProjectile.h"

#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "ProjectMJ.h"
#include "Character/MJCharacterBase.h"
#include "Components/SphereComponent.h"
#include "Physics/MJCollision.h"
#include "Behavior/MJProjectileReactionBehaviorBase.h"
#include "Behavior/MJProjectileMovementBehaviorBase.h"
#include "Behavior/MJProjectileMovementLinear.h"

AMJCollisionProjectile::AMJCollisionProjectile()
{
}

void AMJCollisionProjectile::BeginPlay()
{
	Super::BeginPlay();

	NiagaraComponent->OnSystemFinished.AddDynamic(this, &AMJCollisionProjectile::OnNiagaraEnded);
}

void AMJCollisionProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	AMJCharacterBase* OwnerActor = Cast<AMJCharacterBase>(ProjectileParams.SourceASC->GetAvatarActor());
	if (!OwnerActor)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerActor"));
		return;
	}

	if (OtherActor == this || (OwnerActor && OtherActor == OwnerActor))
	{
		MJ_LOG(LogMJ, Warning, TEXT("Target is User"));
		return;
	}

	USceneComponent* RootComp = OtherActor->GetRootComponent();
	if (!RootComp)
	{
		MJ_LOG(LogMJ, Warning, TEXT("RootComp is nullptr."));
		return;
	}
	
	ECollisionChannel CollisionChannel = RootComp->GetCollisionObjectType();
	if (CollisionChannel == CCHANNEL_MJGROUND)
	{
		MJ_LOG(LogMJ, Warning, TEXT("This Actor is Ground."));
		return;
	}
	
	NiagaraComponent->SetBoolParameter(TEXT("HasCollided"), true);
	// TODO: 콜리전 비활성화

	for (const TObjectPtr <UMJProjectileReactionBehaviorBase> ReactionBehavior : ReactionBehaviors)
	{
		if (ReactionBehavior)
		{
			ReactionBehavior->OnProjectileReact(this, OtherActor, SweepResult);
		}
	}
	
	MJ_LOG(LogMJ, Warning, TEXT("Sphere Overlap"));
}

void AMJCollisionProjectile::OnNiagaraEnded(UNiagaraComponent* PSystem)
{
	Destroy();
}
