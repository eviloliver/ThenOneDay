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
	Sphere->SetCollisionProfileName(CRPOFILE_MJPROJECTILE);

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

}

void AMJProjectileBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (const TObjectPtr <UMJProjectileReactionBehaviorBase> ReactionBehavior : ReactionBehaviors)
	{
		if (ReactionBehavior)
		{
			ReactionBehavior->OnProjectileReact(this, OtherActor, SweepResult);
		}
	}
}