// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/MJTA_SphereTrace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ProjectMJ.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/Character.h"
#include "Physics/MJCollision.h"

AMJTA_SphereTrace::AMJTA_SphereTrace()
{
}

FGameplayAbilityTargetDataHandle AMJTA_SphereTrace::MakeTargetData() const
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (!ASC)
	{
		MJ_LOG(LogMJ, Error, TEXT("ASC not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	const UMJCharacterSkillAttributeSet* SkillAttributeSet = ASC->GetSet<UMJCharacterSkillAttributeSet>();
	if (!SkillAttributeSet)
	{
		MJ_LOG(LogMJ, Error, TEXT("SkillAttributeSet not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	TArray<FOverlapResult> Overlaps;

	const float AttackRadius = SkillAttributeSet->GetSkillRadius();

	FVector OriginLocation = Character->GetActorLocation();
	FCollisionQueryParams Params(SCENE_QUERY_STAT(UMJTA_Trace), false, Character);
	GetWorld()->OverlapMultiByChannel(Overlaps, OriginLocation, FQuat::Identity, CCHANNEL_MJAbilityTargetTrace, FCollisionShape::MakeSphere(AttackRadius), Params);

	TArray<TWeakObjectPtr<AActor>> HitActors;
	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* HitActor = Overlap.OverlapObjectHandle.FetchActor<AActor>();
		if (HitActor && !HitActors.Contains(HitActor))
		{
			HitActors.Add(HitActor);
		}
	}
	FGameplayAbilityTargetData_ActorArray* ActorData = new FGameplayAbilityTargetData_ActorArray();
	ActorData->SetActors(HitActors);

#if ENABLE_DRAW_DEBUG
	if (bShowDebug)
	{
		FColor DrawColor = HitActors.Num() > 0 ? FColor::Green : FColor::Red;
		DrawDebugSphere(GetWorld(), OriginLocation, AttackRadius, 16, DrawColor, false, 5.0f);
	}

#endif
	return FGameplayAbilityTargetDataHandle(ActorData);
}

