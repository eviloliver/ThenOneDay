// ThenOneDayStudio


#include "AbilitySystem/TargetActor/MJTA_CustomTrace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "ProjectMJ.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/Character.h"
#include "Physics/MJCollision.h"

class UMJCharacterSkillAttributeSet;

AMJTA_CustomTrace::AMJTA_CustomTrace()
{
	TraceLocation = FVector::ZeroVector;
	TraceShape = ETraceShape::Sphere;
}

FGameplayAbilityTargetDataHandle AMJTA_CustomTrace::MakeTargetData() const
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

	const FVector OriginLocation = (TraceLocation==FVector::ZeroVector?Character->GetActorLocation():TraceLocation);
	const FVector Forward = Character->GetActorForwardVector();
	const float Offset = SkillAttributeSet->GetSkillAttackLocationOffset();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(UMJTA_Trace), false, Character);
	
	TArray<FOverlapResult> OutOverlapResults;
	
	switch (TraceShape)
	{
	case ETraceShape::Sphere:
		{
			// Sphere
	
			FVector Center = OriginLocation + Forward * ((Offset!=0)?Offset:1);
			GetWorld()->OverlapMultiByChannel(OutOverlapResults, Center, FQuat::Identity, CCHANNEL_MJAbilityTargetTrace, FCollisionShape::MakeSphere(AttackRadius), Params);
		}
	case ETraceShape::Capsule:
		{
			// Capsule
			const FVector Start = OriginLocation + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius() * ((Offset != 0) ? Offset : 1);
			const FVector End = Start + Forward * AttackRange;
			const FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
			float CapsuleHalfHeight = AttackRange * 0.5f;
			
			GetWorld()->OverlapMultiByChannel(OutOverlapResults, CapsuleOrigin, FRotationMatrix::MakeFromZ(Forward).ToQuat(), CCHANNEL_MJAbilityTargetTrace, FCollisionShape::MakeCapsule(AttackRadius, CapsuleHalfHeight), Params);

		}
	}

	/*
	* Minjin
	* HowTo: 적끼리 공격하지 않는다.
	* FGameplayTargetDataFilter 생성, RequiredActorClass로 SourceActor의 C++ 클래스를 설정한다.
	* -> 이러면 FilterPassesForActor 중 !ActorToBeFiltered(HitActor를 뜻함)->IsA(RequiredActorClass)에 걸려 false를 리턴: Target 대상에서 제외됨
	* => bReverseFilter를 true로 한다...
	*/

	TSubclassOf<AActor> ActorClass = GetParentNativeClass(SourceActor.GetClass());
	
	FGameplayTargetDataFilter FilteringData;
	FilteringData.RequiredActorClass = ActorClass;
	FilteringData.bReverseFilter = true;
	FilteringData.InitializeFilterContext(SourceActor);
	
	TArray<TWeakObjectPtr<AActor>> HitActors;
	for (const FOverlapResult& Overlap : OutOverlapResults)
	{
		AActor* HitActor = Overlap.OverlapObjectHandle.FetchActor<AActor>();
		if (HitActor && !HitActors.Contains(HitActor)&& (FilteringData.FilterPassesForActor(HitActor)))
		{
			HitActors.Add(HitActor);
		}
	}
	FGameplayAbilityTargetData_ActorArray* ActorData = new FGameplayAbilityTargetData_ActorArray();
	ActorData->SetActors(HitActors);

	return FGameplayAbilityTargetDataHandle(ActorData);
}
