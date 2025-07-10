// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Actor/MJProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Physics/MJCollision.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"

AMJProjectileBase::AMJProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Sphere Section
	Sphere = CreateDefaultSubobject<USphereComponent>("Projectile");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(CCHANNEL_MJPROJECTILE);
	Sphere->SetCollisionProfileName(CRPOFILE_MJPROJECTILE);

	// Movement Section
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	// Niagara Section
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	NiagaraComponent->SetupAttachment(RootComponent);

}

void AMJProjectileBase::InitProjectileParams(const FMJSkillProjectileParams& InParams)
{
	ProjectileParams = InParams;

	if (ProjectileParams.ProjectileSpeed > 0.0f)
	{
		ProjectileMovement->InitialSpeed = ProjectileParams.ProjectileSpeed;
		ProjectileMovement->MaxSpeed = ProjectileParams.ProjectileSpeed;
	}
	if (ProjectileParams.SkillRadius > 0.0f)
	{
		Sphere->SetSphereRadius(ProjectileParams.SkillRadius);
	}
}

void AMJProjectileBase::ApplyGameplayEffects(UAbilitySystemComponent* Target, const FHitResult& HitResult)
{
	ProjectileParams.TargetASC = Target;

	// 이펙트 하나여야 하는데
	for (const TSubclassOf<UGameplayEffect> EffectClass : ProjectileParams.GameplayEffects)
	{
		if (EffectClass)
		{
			FGameplayEffectContextHandle EffectContext = ProjectileParams.SourceASC->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle SpecHandle = ProjectileParams.SourceASC->MakeOutgoingSpec(EffectClass, 1.0f, EffectContext);
			if (SpecHandle.IsValid())
			{
				SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.BaseDamage")), ProjectileParams.BaseDamage);
				SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AttackDamageScaling")), ProjectileParams.AttackDamageScaling);
				SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AbilityPowerScaling")), ProjectileParams.AbilityPowerScaling);
				SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.MaxLifeSteal")), ProjectileParams.LifeSteal);
				SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectChance")), ProjectileParams.StatusEffectChance);
				SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectDuration")), ProjectileParams.StatusEffectDuration);

				ProjectileParams.SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ProjectileParams.TargetASC);
			}

			if (HitGameplayCueTag.IsValid())
			{
				FGameplayEffectContextHandle CueContextHandle = UAbilitySystemBlueprintLibrary::GetEffectContext(SpecHandle);
				CueContextHandle.AddHitResult(HitResult);

				FGameplayCueParameters CueParams;
				CueParams.EffectContext = CueContextHandle;

				Target->ExecuteGameplayCue(HitGameplayCueTag, CueParams);
			}
		}
	}
}

void AMJProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMJProjectileBase::OnSphereOverlap);

}

void AMJProjectileBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !ProjectileParams.SourceASC)
	{
		return;
	}

	if (OtherActor == ProjectileParams.SourceASC->GetAvatarActor())
	{
		// 콜리전 프로파일에 설정해줬지만 그래도 걸어두기
		// I've set it up in the collisions profile, but I'm still dealing with exceptions
		return;
	}

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (!TargetASC)
	{
		return;
	}

	FVector EffectLocation = SweepResult.ImpactPoint;
	if (EffectLocation.IsNearlyZero())
	{
		EffectLocation = GetActorLocation(); // or TargetActor->GetActorLocation()
	}

	ApplyGameplayEffects(TargetASC, SweepResult);

	// HandleProjectileDestroy();

	// TODO: 나중에 통과하는 투사체인지 결정
	// TODO: 투사체 갯수는 생성하는 쪽에서 결정할 거 같긴 한데 이거 어떻게 하면 좋을지
	// 벽이나 다른 곳에 닿으면 사라지게? 아니면 그냥 시간 지나면 사라지게

	// Destroyed();
}