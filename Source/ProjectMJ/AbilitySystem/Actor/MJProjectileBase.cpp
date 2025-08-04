// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Actor/MJProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "Physics/MJCollision.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "Behavior/MJProjectileReactionBehaviorBase.h"
#include "Behavior/MJProjectileMovementBehaviorBase.h"

AMJProjectileBase::AMJProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Sphere Section
	Sphere = CreateDefaultSubobject<USphereComponent>("Projectile");
	SetRootComponent(Sphere);

	Sphere->SetCollisionObjectType(CCHANNEL_MJPROJECTILE);

	Sphere->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Niagara Section
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	NiagaraComponent->SetupAttachment(RootComponent);
}

void AMJProjectileBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MovementBehavior)
	{
		MovementBehavior->Move(this, DeltaSeconds);
	}
}

void AMJProjectileBase::InitProjectile(const FMJSkillProjectileParams& InParams,
	TSubclassOf<UMJProjectileMovementBehaviorBase> InMovementBehaviorClass,
	const TArray<TSubclassOf<UMJProjectileReactionBehaviorBase>>& InReactionBehaviorClasses)
{
	ProjectileParams = InParams;

	if (InMovementBehaviorClass)
	{
		MovementBehavior = NewObject<UMJProjectileMovementBehaviorBase>(this, InMovementBehaviorClass);
		if (MovementBehavior)
		{
			MovementBehavior->InitMovement(this);
		}
	}

	for (const auto& ReactionBehaviorClass : InReactionBehaviorClasses)
	{
		if (ReactionBehaviorClass)
		{
			UMJProjectileReactionBehaviorBase* ReactionBehavior = NewObject<UMJProjectileReactionBehaviorBase>(this, ReactionBehaviorClass);
			if (ReactionBehavior)
			{
				ReactionBehavior->InitReaction(this);
				ReactionBehaviors.Add(ReactionBehavior);
			}
		}
	}

	if (ProjectileParams.SkillRadius > 0.0f)
	{
		Sphere->SetSphereRadius(ProjectileParams.SkillRadius);

	}
}

void AMJProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMJProjectileBase::OnSphereOverlap);
	Sphere->OnComponentHit.AddDynamic(this, &AMJProjectileBase::OnSphereHit);

	if (ProjectileParams.LifeSpan > 0.0f)
	{
		SetLifeSpan(ProjectileParams.LifeSpan);
	}
}

void AMJProjectileBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool bIsLastPierce = false;

	if (ProjectileParams.PierceCount > 0)
	{
		--ProjectileParams.PierceCount;
		if (ProjectileParams.PierceCount <= 0)
		{
			bIsLastPierce = true;
		}
	}
	else
	{
		bIsLastPierce = true;
	}

	for (const TObjectPtr <UMJProjectileReactionBehaviorBase> ReactionBehavior : ReactionBehaviors)
	{
		if (ReactionBehavior)
		{
			ReactionBehavior->OnProjectileReact(this, OtherActor, SweepResult);
		}
	}

	if (bIsLastPierce)
	{
		Destroy();
	}
}

void AMJProjectileBase::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	for (const TObjectPtr <UMJProjectileReactionBehaviorBase> ReactionBehavior : ReactionBehaviors)
	{
		if (ReactionBehavior)
		{
			ReactionBehavior->OnProjectileReact(this, OtherActor, Hit);
		}
	}
	Destroy();
}
