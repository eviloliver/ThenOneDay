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
	const FVector Forward = Character->GetActorForwardVector();
	const float Offset = SkillAttributeSet->GetSkillAttackLocationOffset();

	FVector Center = OriginLocation + Forward * ((Offset!=0)?Offset:1);
	FCollisionQueryParams Params(SCENE_QUERY_STAT(UMJTA_Trace), false, Character);
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CCHANNEL_MJAbilityTargetTrace, FCollisionShape::MakeSphere(AttackRadius), Params);

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
	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* HitActor = Overlap.OverlapObjectHandle.FetchActor<AActor>();
		if (HitActor && !HitActors.Contains(HitActor)&& (FilteringData.FilterPassesForActor(HitActor)))
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
		DrawDebugSphere(GetWorld(), Center, AttackRadius, 16, DrawColor, false, 5.0f);
	}

#endif
	return FGameplayAbilityTargetDataHandle(ActorData);
}

