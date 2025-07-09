// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_BaseProjectile.h"

#include "MJGA_InstantSkill.h"
#include "ProjectMJ.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "Character/MJCharacterBase.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "DataAsset/MJProjectileDataAsset.h"

UMJGA_BaseProjectile::UMJGA_BaseProjectile()
{

}

void UMJGA_BaseProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{


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

    const FGameplayAbilitySpec* CurrentAbilitySpec = GetCurrentAbilitySpec();
    if (!CurrentAbilitySpec)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    // Dongmin: 이동훈 팀장님이 추천해주신거? -> 없으면 그냥 크래쉬 터트리기였나 + 이거 하려면 위에 OwnerCharacter 검사까지 안해버려야 했던거 같음
    // UMJSkillComponent* SkillComponent = OwnerCharacter ? OwnerCharacter->FindComponentByClass<UMJSkillComponent>() : nullptr;

    UMJSkillComponentBase* SkillComponent = OwnerCharacter->FindComponentByClass<UMJSkillComponentBase>();
    if (!SkillComponent)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    FGameplayTag ActionAbilityTag;
    for (const FGameplayAbilitySpec& Spec : SourceASC->GetActivatableAbilities())
    {
        // Dongmin: 어빌리티의 첫 번째 태그를 기본 태그로
        if (Spec.IsActive() && Spec.Ability && Spec.Ability->IsA<UMJGA_InstantSkill>())
        {
	        if (Spec.Ability->AbilityTags.Num() > 0)
	        {
                ActionAbilityTag = Spec.Ability->AbilityTags.GetByIndex(0);
                break;
	        }
        }

    }
    if (!ActionAbilityTag.IsValid() || !SkillComponent->GetOwnedSkillMap().Contains(ActionAbilityTag))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }
    
    const FGameplayTag& ProjectileTagToSpawn = SkillComponent->GetOwnedSkillMap()[ActionAbilityTag].ProjectileTag;
    if (!ProjectileTagToSpawn.IsValid())
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    TSubclassOf<AMJProjectileBase> ProjectileClass = ProjectileDataAsset->FindProjectileClassForTag(ProjectileTagToSpawn);
    if (!ProjectileClass)
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

	FRotator SpawnRotator = OwnerCharacter->GetActorRotation();

	// TODO: 무기의 소켓, Weapon's Socket

	FVector SpawnLocation = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * 100.0f;
	AMJProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AMJProjectileBase>(ProjectileClass, FTransform(SpawnRotator,SpawnLocation), GetOwningActorFromActorInfo(), OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (Projectile)
    {
		Projectile->InitProjectileParams(ProjectileParams);
		Projectile->FinishSpawning(FTransform(SpawnRotator, SpawnLocation));
    }
    EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
    MJ_LOG(LogMJ, Log, TEXT("10"));

}
