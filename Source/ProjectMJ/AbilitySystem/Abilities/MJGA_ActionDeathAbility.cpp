// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_ActionDeathAbility.h"

#include "ProjectMJ.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/MJCharacterBase.h"

UMJGA_ActionDeathAbility::UMJGA_ActionDeathAbility()
{
}

void UMJGA_ActionDeathAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		MJ_LOG(LogMJ, Warning, TEXT("CommitAbility is false"));
		constexpr bool bReplicateEndAbility = true;
		constexpr bool bWasCancelled = true;
		EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
	/////

	if (DeathActionAnimMontage == nullptr)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	AMJCharacterBase* AMJCharacter = Cast<AMJCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!AMJCharacter)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	
	UAbilityTask_PlayMontageAndWait* PlayDeathMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayDeath"), DeathActionAnimMontage, 1.0f);

	PlayDeathMontage->OnCompleted.AddDynamic(this, &UMJGA_ActionDeathAbility::OnCompleteCallback);
	PlayDeathMontage->OnInterrupted.AddDynamic(this, &UMJGA_ActionDeathAbility::OnInterruptedCallback);
	PlayDeathMontage->OnCancelled.AddDynamic(this, &UMJGA_ActionDeathAbility::OnInterruptedCallback);
	PlayDeathMontage->OnBlendOut.AddDynamic(this, &UMJGA_ActionDeathAbility::OnBlendOutCallback);

	PlayDeathMontage->ReadyForActivation();
}

void UMJGA_ActionDeathAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_ActionDeathAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AMJCharacterBase* AMJCharacter = Cast<AMJCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!AMJCharacter)
	{
		return; 
	}

	AMJCharacter->Destroy();
}

void UMJGA_ActionDeathAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_ActionDeathAbility::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_ActionDeathAbility::OnBlendOutCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
