// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_BaseProjectile.h"

#include "ProjectMJ.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "Character/MJCharacterBase.h"
#include "ProjectMJ.h"

UMJGA_BaseProjectile::UMJGA_BaseProjectile()
{
    MJ_LOG(LogMJ, Log, TEXT("14"));

}

void UMJGA_BaseProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{

    MJ_LOG(LogMJ, Log, TEXT("21"));

 	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetAvatarActorFromActorInfo());
    if (!OwnerCharacter)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
    if (!SourceASC)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    const UMJCharacterSkillAttributeSet* SkillAttributeSet = SourceASC->GetSet<UMJCharacterSkillAttributeSet>();
    if (!SkillAttributeSet)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

     FMJSkillProjectileParams ProjectileParams;
     ProjectileParams.SourceASC = SourceASC;
     ProjectileParams.GameplayEffects = GameplayEffectClasses;
     ProjectileParams.BaseDamage = SkillAttributeSet->GetBaseDamage();
     ProjectileParams.AttackDamageScaling = SkillAttributeSet->GetAttackDamageScaling();
     ProjectileParams.AbilityPowerScaling = SkillAttributeSet->GetAbilityPowerScaling();
     ProjectileParams.LifeSteal = SkillAttributeSet->GetLifeSteal();
     ProjectileParams.SkillRadius = SkillAttributeSet->GetSkillRadius();
     ProjectileParams.SkillRange = SkillAttributeSet->GetSkillRange();
     ProjectileParams.StatusEffectChance = SkillAttributeSet->GetStatusEffectChance();
     ProjectileParams.StatusEffectDuration = SkillAttributeSet->GetStatusEffectDuration();
     ProjectileParams.ProjectileSpeed = SkillAttributeSet->GetProjectileSpeed();
     ProjectileParams.ProjectileCount = SkillAttributeSet->GetProjectileCount();
 
    if (ProjectileClass)
    {

    	FRotator SpawnRotator = OwnerCharacter->GetActorRotation();

    	// TODO: 무기의 소켓, Weapon's Socket
        FVector SpawnLocation = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * 100.0f;
    	AMJProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AMJProjectileBase>(ProjectileClass, FTransform(SpawnRotator,SpawnLocation), GetOwningActorFromActorInfo(), OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
 
    	if (Projectile)
    	{
    		Projectile->InitProjectileParams(ProjectileParams);
            Projectile->FinishSpawning(FTransform(SpawnRotator, SpawnLocation));
    	}
    }    
    EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
    
}
