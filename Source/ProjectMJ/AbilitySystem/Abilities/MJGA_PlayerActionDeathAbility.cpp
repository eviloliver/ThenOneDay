// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_PlayerActionDeathAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/MJCharacterBase.h"

UMJGA_PlayerActionDeathAbility::UMJGA_PlayerActionDeathAbility()
{
}

void UMJGA_PlayerActionDeathAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

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

	PlayDeathMontage->OnCompleted.AddDynamic(this, &UMJGA_PlayerActionDeathAbility::OnCompleteCallback);
	PlayDeathMontage->OnInterrupted.AddDynamic(this, &UMJGA_PlayerActionDeathAbility::OnInterruptedCallback);
	PlayDeathMontage->OnCancelled.AddDynamic(this, &UMJGA_PlayerActionDeathAbility::OnInterruptedCallback);
	PlayDeathMontage->OnBlendOut.AddDynamic(this, &UMJGA_PlayerActionDeathAbility::OnBlendOutCallback);

	PlayDeathMontage->ReadyForActivation();
}

void UMJGA_PlayerActionDeathAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_PlayerActionDeathAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	// Minjin: Super 호출 전 필요한 거 작업
	

	// Minjin: Super에서 Destroy하는데 바꿔도 됨
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMJGA_PlayerActionDeathAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_PlayerActionDeathAbility::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_PlayerActionDeathAbility::OnBlendOutCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
