// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_MeleeAttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ProjectMJ.h"
#include "AbilitySystem/AbilityTasks/MJAT_Trace.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

UMJGA_MeleeAttackHitCheck::UMJGA_MeleeAttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMJGA_MeleeAttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	MJ_LOG(LogMJ, Log, TEXT("%s"), *TriggerEventData->EventTag.GetTagName().ToString());

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMJAT_Trace* AttackTraceTask = UMJAT_Trace::CreateTask(this, TargetActorClass);
	AttackTraceTask->OnComplete.AddDynamic(this, &UMJGA_MeleeAttackHitCheck::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();

}

void UMJGA_MeleeAttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		// 이거 가까운거 하나만 검사하는건데 나중에 수정할 필요 있어보임

		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
		// null check 해야함
		// GameplayCue 에 사용함

		const UMJCharacterAttributeSet* SourceCharacterAttributeSet = SourceASC->GetSet<UMJCharacterAttributeSet>();
		const UMJCharacterSkillAttributeSet* SourceCharacterSkillAttributeSet = SourceASC->GetSet<UMJCharacterSkillAttributeSet>();
		// null check 해야함
		// GE 없이 테스트 할 때 사용해 볼 것

		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
		if (EffectSpecHandle.IsValid())
		{
			MJ_LOG(LogMJ, Warning, TEXT("GA: EffectSpecHandle.Data (before set) address: %p"), EffectSpecHandle.Data.Get());

			EffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.BaseDamage")), SourceCharacterSkillAttributeSet->GetBaseDamage());
			EffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AttackDamageScaling")), SourceCharacterSkillAttributeSet->GetAttackDamageScaling());
			EffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AbilityPowerScaling")), SourceCharacterSkillAttributeSet->GetAbilityPowerScaling());
			MJ_LOG(LogMJ, Warning, TEXT("GA: BaseDamage after setting on SpecHandle.Data: %f"), EffectSpecHandle.Data->GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.BaseDamage")), false));
			MJ_LOG(LogMJ, Warning, TEXT("GA: EffectSpecHandle.Data (after set) address: %p"), EffectSpecHandle.Data.Get());
			MJ_LOG(LogMJ,Warning, TEXT("%f %f %f"), SourceCharacterSkillAttributeSet->GetBaseDamage(), SourceCharacterSkillAttributeSet->GetAttackDamageScaling(), SourceCharacterSkillAttributeSet->GetAbilityPowerScaling())
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);

			// TODO : GameplayCue
		}
	}
	else if (UAbilitySystemBlueprintLibrary::TargetDataHasActor(TargetDataHandle, 0))
	{
		// Gameplay Cue 에 사용
		// UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();

		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);

		if (EffectSpecHandle.IsValid())
		{

			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);

			// TODO : GameplayCue
		}
	}
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
