// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_PlayerActionDamageAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/MJCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UMJGA_PlayerActionDamageAbility::UMJGA_PlayerActionDamageAbility()
{
}

void UMJGA_PlayerActionDamageAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (HurtActionAnimMontage == nullptr)
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
	
	UAbilityTask_PlayMontageAndWait* PlayHurtMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayHurt"), HurtActionAnimMontage, 1.0f);

	PlayHurtMontage->OnCompleted.AddDynamic(this, &UMJGA_PlayerActionDamageAbility::OnCompleteCallback);
	PlayHurtMontage->OnInterrupted.AddDynamic(this, &UMJGA_PlayerActionDamageAbility::OnInterruptedCallback);
	PlayHurtMontage->OnCancelled.AddDynamic(this, &UMJGA_PlayerActionDamageAbility::OnInterruptedCallback);

	PlayHurtMontage->ReadyForActivation();
}

void UMJGA_PlayerActionDamageAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_PlayerActionDamageAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMJGA_PlayerActionDamageAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_PlayerActionDamageAbility::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_PlayerActionDamageAbility::OnBlendOutCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
