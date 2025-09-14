// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_SpawnProjectile.h"

#include "MJGA_InstantSkill.h"
#include "ProjectMJ.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "AbilitySystem/Actor/Behavior/MJProjectileMovementBehaviorBase.h"
#include "Character/MJCharacterBase.h"
#include "Character/Component/MJAbilityContextComponent.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "Kismet/GameplayStatics.h"

UMJGA_SpawnProjectile::UMJGA_SpawnProjectile()
{

}

void UMJGA_SpawnProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{


 	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetAvatarActorFromActorInfo());
    if (!OwnerCharacter)
    {
        MJ_LOG(LogMJ, Warning, TEXT("Not Exist OwnerCharacter"));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
    if (!SourceASC)
    {
        MJ_LOG(LogMJ, Warning, TEXT("Not Exist SourceASC"));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    const UMJCharacterSkillAttributeSet* SkillAttributeSet = SourceASC->GetSet<UMJCharacterSkillAttributeSet>();
    if (!SkillAttributeSet)
    {
        MJ_LOG(LogMJ, Warning, TEXT("Not Exist SkillAttributeSet"));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    const FGameplayAbilitySpec* CurrentAbilitySpec = GetCurrentAbilitySpec();
    if (!CurrentAbilitySpec)
    {
        MJ_LOG(LogMJ, Warning, TEXT("Not Exist CurrentAbilitySpec"));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    if (!ProjectileClass)
    {
        MJ_LOG(LogMJ, Warning, TEXT("Not Exist ProjectileClass"));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    if (!MovementBehavior)
    {
        MJ_LOG(LogMJ, Warning, TEXT("Not Exist MovementBehavior"));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    UMJProjectileMovementBehaviorBase* MovementStrategy = MovementBehavior->GetDefaultObject <UMJProjectileMovementBehaviorBase>();
    if (!MovementStrategy)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    FVector MouseLocation = FVector::ZeroVector;
    if (UMJAbilityContextComponent* ContextComponent = OwnerCharacter->FindComponentByClass<UMJAbilityContextComponent>())
    {
        MouseLocation = ContextComponent->LastTargetedMouseLocation;
        ContextComponent->LastTargetedMouseLocation = FVector::ZeroVector;
    }

    if (MouseLocation == FVector::ZeroVector)
    {
        MouseLocation = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * 1000.f;
    }

    const FTransform SpawnTransform = MovementStrategy->CalculateSpawnTransform(this, MouseLocation, SpawnSocketName);

    AMJProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AMJProjectileBase>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

    if (Projectile)
    {
        FMJSkillProjectileParams ProjectileParams;
        ProjectileParams.TargetLocation = MouseLocation;

        ProjectileParams.SourceASC = SourceASC;

        ProjectileParams.DamageGameplayEffectClass = DamageGameplayEffectClass;
        ProjectileParams.StatusGameplayEffectClass = StatusGameplayEffectClass;
        ProjectileParams.ExplosionDamageGameplayEffectClass = ExplosionDamageGameplayEffectClass;

        ProjectileParams.BaseDamage = SkillAttributeSet->GetBaseDamage();
        ProjectileParams.AttackDamageScaling = SkillAttributeSet->GetAttackDamageScaling();
        ProjectileParams.AbilityPowerScaling = SkillAttributeSet->GetAbilityPowerScaling();
        ProjectileParams.LifeSteal = SkillAttributeSet->GetLifeSteal();
        ProjectileParams.SkillRadius = SkillAttributeSet->GetSkillRadius();
        ProjectileParams.SkillRange = SkillAttributeSet->GetSkillRange();

        ProjectileParams.StatusEffectChance = SkillAttributeSet->GetStatusEffectChance();
        ProjectileParams.StatusEffectDuration = SkillAttributeSet->GetStatusEffectDuration();
        ProjectileParams.StatusEffectBaseDamage = SkillAttributeSet->GetStatusBaseDamage();
        ProjectileParams.StatusEffectADScaling = SkillAttributeSet->GetStatusEffectADScaling();
        ProjectileParams.StatusEffectAPScaling = SkillAttributeSet->GetStatusEffectAPScaling();
        ProjectileParams.StatusEffectMaxStack = SkillAttributeSet->GetStatusEffectMaxStack();
        ProjectileParams.StatusEffectPeriod = SkillAttributeSet->GetStatusEffectPeriod();
        ProjectileParams.StatusEffectSlowPercent = SkillAttributeSet->GetStatusEffectSlowPercent();

        ProjectileParams.ExplosionRadius = SkillAttributeSet->GetExplosionRadius();
        ProjectileParams.ExplosionBaseDamage = SkillAttributeSet->GetExplosionBaseDamage();
        ProjectileParams.ExplosionADScaling = SkillAttributeSet->GetExplosionADScaling();
        ProjectileParams.ExplosionAPScaling = SkillAttributeSet->GetExplosionAPScaling();

        ProjectileParams.ProjectileSpeed = SkillAttributeSet->GetProjectileSpeed();
        ProjectileParams.ProjectileCount = SkillAttributeSet->GetProjectileCount();
        ProjectileParams.LifeSpan = SkillAttributeSet->GetProjectileLifeSpan();

        ProjectileParams.PierceCount = SkillAttributeSet->GetProjectilePierceCount();

        Projectile->InitProjectile(ProjectileParams, MovementBehavior, ReactionBehaviors);

        UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);

    }

    EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}
