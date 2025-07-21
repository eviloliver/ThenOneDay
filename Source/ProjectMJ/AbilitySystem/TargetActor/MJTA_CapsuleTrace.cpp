// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/MJTA_CapsuleTrace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ProjectMJ.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Physics/MJCollision.h"
#include "Engine/OverlapResult.h"


AMJTA_CapsuleTrace::AMJTA_CapsuleTrace()
{
}

FGameplayAbilityTargetDataHandle AMJTA_CapsuleTrace::MakeTargetData() const
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

	const float AttackRadius = SkillAttributeSet->GetSkillRadius();
	const float AttackRange = SkillAttributeSet->GetSkillRange();

	FVector OriginLocation = Character->GetActorLocation();
	FCollisionQueryParams Params(SCENE_QUERY_STAT(UMJTA_Trace), false, Character);
	const FVector Forward = Character->GetActorForwardVector();
	const FVector Start = OriginLocation + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + Forward * AttackRange;

	TArray<FHitResult> OutHitResults;
	GetWorld()->SweepMultiByChannel(OutHitResults, Start, End, FQuat::Identity, CCHANNEL_MJAbilityTargetTrace, FCollisionShape::MakeSphere(AttackRadius), Params);


	TArray<TWeakObjectPtr<AActor>> HitActors;
	for (const FHitResult& OutHitResult : OutHitResults)
	{
		AActor* HitActor = OutHitResult.GetActor();
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
		FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
		float CapsuleHalfHeight = AttackRange * 0.5f;
		FColor DrawColor = OutHitResults.Num() != 0 ? FColor::Green : FColor::Red;
		DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor, false, 5.0f);
	}

#endif
	return FGameplayAbilityTargetDataHandle(ActorData);
}
