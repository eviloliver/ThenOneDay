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
	const float AttackRange = FMath::Max(SkillAttributeSet->GetSkillRange(), AttackRadius * 2.0f);
	const float Offset = SkillAttributeSet->GetSkillAttackLocationOffset();

	const FVector OriginLocation = Character->GetActorLocation();
	const FVector Forward = Character->GetActorForwardVector();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(UMJTA_Trace), false, Character);

	const FVector Start = OriginLocation + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius() * ((Offset != 0) ? Offset : 1);
	const FVector End = Start + Forward * AttackRange;
	const FVector CapsuleOrigin = Start + (End - Start) * 0.5f;

	float CapsuleHalfHeight = AttackRange * 0.5f;

	TArray<FOverlapResult> OutHitResults;
	GetWorld()->OverlapMultiByChannel(OutHitResults, CapsuleOrigin, FRotationMatrix::MakeFromZ(Forward).ToQuat(), CCHANNEL_MJAbilityTargetTrace, FCollisionShape::MakeCapsule(AttackRadius, CapsuleHalfHeight), Params);

	/*
	 * Minjin
	 * HowTo: 적끼리 공격하지 않는다.
	 * FGameplayTargetDataFilter 생성, RequiredActorClass로 SourceActor의 C++ 클래스를 설정한다.
	 * -> 이러면 FilterPassesForActor 중 !ActorToBeFiltered(HitActor를 뜻함)->IsA(RequiredActorClass)에 걸려 false를 리턴: Target 대상에서 제외됨
	 * => bReverseFilter를 true로 한다...
	 */
	 // Minjin: 다른 방법이 있다면 알려주세요....

	TSubclassOf<AActor> ActorClass = GetParentNativeClass(SourceActor.GetClass());

	FGameplayTargetDataFilter FilteringData;
	FilteringData.RequiredActorClass = ActorClass;
	FilteringData.bReverseFilter = true;
	FilteringData.InitializeFilterContext(SourceActor);

	TArray<TWeakObjectPtr<AActor>> HitActors;
	for (const FOverlapResult& OutHitResult : OutHitResults)
	{
		AActor* HitActor = OutHitResult.GetActor();

		// Minjin: Filter를 통과하면(공격대상) HitActor에 추가
		if (HitActor && !HitActors.Contains(HitActor) && (FilteringData.FilterPassesForActor(HitActor)))
		{
			HitActors.Add(HitActor);
		}
	}
	FGameplayAbilityTargetData_ActorArray* ActorData = new FGameplayAbilityTargetData_ActorArray();
	ActorData->SetActors(HitActors);

#if ENABLE_DRAW_DEBUG
	if (bShowDebug)
	{
		FColor DrawColor = OutHitResults.Num() != 0 ? FColor::Green : FColor::Red;
		DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor, false, 5.0f);
	}

#endif
	return FGameplayAbilityTargetDataHandle(ActorData);
}