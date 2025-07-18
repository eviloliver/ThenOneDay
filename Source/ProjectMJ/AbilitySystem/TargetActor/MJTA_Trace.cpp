// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/MJTA_Trace.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

AMJTA_Trace::AMJTA_Trace()
{
}

void AMJTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void AMJTA_Trace::ConfirmTargetingAndContinue()
{
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
		TargetDataReadyDelegate.Broadcast(DataHandle);
	}
}

FGameplayAbilityTargetDataHandle AMJTA_Trace::MakeTargetData() const
{
	// 언리얼의 UCLASS는 순수 가상함수가 되지 않아서 원형으로 못 쓰게했음
	// 오버라이드 해라
	checkNoEntry();
	return FGameplayAbilityTargetDataHandle();
}
