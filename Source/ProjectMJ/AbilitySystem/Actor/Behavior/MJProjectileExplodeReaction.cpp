// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileExplodeReaction.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "Character/MJCharacterBase.h"
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

	Explode();
}

void UMJProjectileExplodeReaction::Explode()
{
	const FVector ExplosionLocation = OwnerProjectile->GetActorLocation();
	const float ExplosionRadius = OwnerProjectile->ProjectileParams.ExplosionRadius;

	// 이거 Cue 억지로 쓴 느낌
	// 그냥 Niagara System 달아줘서 재생했어도 될거 같음
	FGameplayCueParameters CueParams;
	CueParams.Location = ExplosionLocation;
	CueParams.RawMagnitude = ExplosionRadius;

	OwnerProjectile->ProjectileParams.SourceASC->ExecuteGameplayCue(GameplayCueTag, CueParams);

	TArray<AActor*> OverlappedActors;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(OwnerProjectile);
	ActorsToIgnore.Add(OwnerProjectile->ProjectileParams.SourceASC->GetAvatarActor());



	UKismetSystemLibrary::SphereOverlapActors(
		OwnerProjectile->GetWorld(),
		ExplosionLocation,
		ExplosionRadius,
		TArray<TEnumAsByte< EObjectTypeQuery >>(),
		AMJCharacterBase::StaticClass(),
		ActorsToIgnore,
		OverlappedActors);

	/*DrawDebugSphere(
		OwnerProjectile->GetWorld(),
		ExplosionLocation,
		ExplosionRadius,
		24,
		FColor::Red,
		false,
		5.0f,
		0,
		1.0f
	);*/

	MJ_LOG(LogMJ, Warning, TEXT("A"));
	for (AActor* OverlappedActor : OverlappedActors)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OverlappedActor);
		if (!TargetASC)
		{
			MJ_LOG(LogMJ, Warning, TEXT("Not Exist TargetASC"));
			continue;
		}
		MJ_LOG(LogMJ, Warning, TEXT("AA"));

		FGameplayEffectContextHandle EffectContext = OwnerProjectile->ProjectileParams.SourceASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		const TSubclassOf<UGameplayEffect> DamageEffectClass = OwnerProjectile->ProjectileParams.ExplosionDamageGameplayEffectClass;
		if (DamageEffectClass)
		{
			FGameplayEffectSpecHandle DamageEffectSpecHandle = OwnerProjectile->ProjectileParams.SourceASC->MakeOutgoingSpec(DamageEffectClass, 1.0f, EffectContext);
			if (DamageEffectSpecHandle.IsValid())
			{
				// 전용 데미지 계산 만든게 아니라서 넘겨주는 태그가 같다
				DamageEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.BaseDamage")), OwnerProjectile->ProjectileParams.ExplosionBaseDamage);
				DamageEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AttackDamageScaling")), OwnerProjectile->ProjectileParams.ExplosionADScaling);
				DamageEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AbilityPowerScaling")), OwnerProjectile->ProjectileParams.ExplosionAPScaling);

				OwnerProjectile->ProjectileParams.SourceASC->ApplyGameplayEffectSpecToTarget(*DamageEffectSpecHandle.Data.Get(), TargetASC);
			}
		}

		const TSubclassOf<UGameplayEffect> StatusEffectClass = OwnerProjectile->ProjectileParams.StatusGameplayEffectClass;
		if (StatusEffectClass)
		{
			FGameplayEffectSpecHandle StatusEffectSpecHandle = OwnerProjectile->ProjectileParams.SourceASC->MakeOutgoingSpec(StatusEffectClass, 1.0f, EffectContext);
			if (StatusEffectSpecHandle.IsValid())
			{
				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectDuration")), OwnerProjectile->ProjectileParams.StatusEffectDuration);

				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusBaseDamage")), OwnerProjectile->ProjectileParams.StatusEffectBaseDamage);
				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectADScaling")), OwnerProjectile->ProjectileParams.StatusEffectADScaling);
				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectAPScaling")), OwnerProjectile->ProjectileParams.StatusEffectAPScaling);

				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectMaxStack")), OwnerProjectile->ProjectileParams.StatusEffectMaxStack);
				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectPeriod")), OwnerProjectile->ProjectileParams.StatusEffectPeriod);

				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectSlowPercent")), OwnerProjectile->ProjectileParams.StatusEffectSlowPercent);
				OwnerProjectile->ProjectileParams.SourceASC->ApplyGameplayEffectSpecToTarget(*StatusEffectSpecHandle.Data.Get(), TargetASC);
			}
		}
	}
}
