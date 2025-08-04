// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileExplodeReaction.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "Kismet/GameplayStatics.h"

UMJProjectileExplodeReaction::UMJProjectileExplodeReaction()
{
}

void UMJProjectileExplodeReaction::InitReaction(AMJProjectileBase* InProjectile)
{
	OwnerProjectile = InProjectile;

}
void UMJProjectileExplodeReaction::OnProjectileReact(AMJProjectileBase* InProjectile, AActor* HitActor, const FHitResult& Hit)
{
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	if (!HitActor)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist HitActor"));
		return;
	}

	if (HitActor == OwnerProjectile->ProjectileParams.SourceASC->GetAvatarActor())
	{
		MJ_LOG(LogMJ, Warning, TEXT("HitActor is User"));
		return;
	}

	// 이거 Cue 억지로 쓴 느낌
	// 그냥 Niagara System 달아줘서 재생했어도 될거 같음
	FGameplayCueParameters CueParams;
	CueParams.Location = OwnerProjectile->GetActorLocation();
	OwnerProjectile->ProjectileParams.SourceASC->ExecuteGameplayCue(GameplayCueTag, CueParams);

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor);
	if (!TargetASC)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist TargetASC"));
		return;
	}

	FGameplayEffectContextHandle EffectContext = OwnerProjectile->ProjectileParams.SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);


	Explode();
}

void UMJProjectileExplodeReaction::Explode()
{
	if (!OwnerProjectile)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerProjectile"));
		return;
	}

	FGameplayCueParameters CueParams;

}
