// ThenOneDayStudio


#include "AbilitySystem/Actor/Behavior/MJProjectileImpactReaction.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "ProjectMJ.h"

UMJProjectileImpactReaction::UMJProjectileImpactReaction()
{
}

void UMJProjectileImpactReaction::InitReaction(AMJProjectileBase* Projectile)
{
	OwnerProjectile = Projectile;
}

void UMJProjectileImpactReaction::OnProjectileReact(AMJProjectileBase* Projectile, AActor* HitActor,
	const FHitResult& Hit)
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

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor);
	if (!TargetASC)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist TargetASC"));
		return;
	}

	FGameplayEffectContextHandle EffectContext = OwnerProjectile->ProjectileParams.SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const TSubclassOf<UGameplayEffect> DamageEffectClass = OwnerProjectile->ProjectileParams.DamageGameplayEffectClass;
	if (DamageEffectClass)
	{
		FGameplayEffectSpecHandle DamageEffectSpecHandle = OwnerProjectile->ProjectileParams.SourceASC->MakeOutgoingSpec(DamageEffectClass, 1.0f, EffectContext);
		if (DamageEffectSpecHandle.IsValid())
		{
			DamageEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.BaseDamage")), OwnerProjectile->ProjectileParams.BaseDamage);
			DamageEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AttackDamageScaling")), OwnerProjectile->ProjectileParams.AttackDamageScaling);
			DamageEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AbilityPowerScaling")), OwnerProjectile->ProjectileParams.AbilityPowerScaling);

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
