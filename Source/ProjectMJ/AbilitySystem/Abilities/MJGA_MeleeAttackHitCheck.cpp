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
	TArray<AActor*> HitActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TargetDataHandle,0);

	if (HitActors.Num() > 0)
	{
		if (!DamageGameplayEffectClass)
		{
			MJ_LOG(LogMJ, Warning, TEXT("Not Exist DamageGameplayEffectClass"));
			return;
		}

		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
		if (!SourceASC)
		{
			MJ_LOG(LogMJ, Warning, TEXT("Not Exist SourceASC"));
			return;
		}

		const UMJCharacterSkillAttributeSet* SourceCharacterSkillAttributeSet = SourceASC->GetSet<UMJCharacterSkillAttributeSet>();

		if (!SourceCharacterSkillAttributeSet)
		{
			MJ_LOG(LogMJ, Warning, TEXT("Not Exist SourceCharacterSkillAttributeSet"));
			return;
		}

		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffectClass);
		if (EffectSpecHandle.IsValid())
		{
			EffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.BaseDamage")), SourceCharacterSkillAttributeSet->GetBaseDamage());
			EffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AttackDamageScaling")), SourceCharacterSkillAttributeSet->GetAttackDamageScaling());
			EffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.AbilityPowerScaling")), SourceCharacterSkillAttributeSet->GetAbilityPowerScaling());

			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);

			for (AActor* HitActor : HitActors)
			{
				UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor);
				if (TargetASC)
				{
					FGameplayCueParameters CueParams;
					CueParams.EffectContext = UAbilitySystemBlueprintLibrary::GetEffectContext(EffectSpecHandle);
					TargetASC->ExecuteGameplayCue(GameplayCueTag, CueParams);
				}
			}
		}

		if (!StatusGameplayEffectClass)
		{
			MJ_LOG(LogMJ, Warning, TEXT("Not Exist DamageGameplayEffectClass"));
			return;
		}
		
		FGameplayEffectSpecHandle StatusEffectSpecHandle = MakeOutgoingGameplayEffectSpec(StatusGameplayEffectClass);
		if (StatusEffectSpecHandle.IsValid())
		{
			float Chance = SourceCharacterSkillAttributeSet->GetStatusEffectChance();

			// TODO: È®·ü °³¼±
			if (FMath::FRandRange(0.0f, 100.0f) <= Chance)
			{
				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectDuration")), SourceCharacterSkillAttributeSet->GetStatusEffectDuration());

				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusBaseDamage")), SourceCharacterSkillAttributeSet->GetStatusBaseDamage());
				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectADScaling")), SourceCharacterSkillAttributeSet->GetStatusEffectADScaling());
				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectAPScaling")), SourceCharacterSkillAttributeSet->GetStatusEffectAPScaling());

				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectMaxStack")), SourceCharacterSkillAttributeSet->GetStatusEffectMaxStack());
				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectPeriod")), SourceCharacterSkillAttributeSet->GetStatusEffectPeriod());

				StatusEffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.StatusEffectSlowPercent")), SourceCharacterSkillAttributeSet->GetStatusEffectSlowPercent());

				ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, StatusEffectSpecHandle, TargetDataHandle);
			}
		}
	}
	
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
