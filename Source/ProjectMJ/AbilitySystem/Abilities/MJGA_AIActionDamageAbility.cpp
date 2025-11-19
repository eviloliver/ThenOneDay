// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_AIActionDamageAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/MJCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UMJGA_AIActionDamageAbility::UMJGA_AIActionDamageAbility()
{
}

void UMJGA_AIActionDamageAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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

	AMJCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);
	
	UAbilityTask_PlayMontageAndWait* PlayHurtMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayHurt"), HurtActionAnimMontage, 1.0f);

	PlayHurtMontage->OnCompleted.AddDynamic(this, &UMJGA_AIActionDamageAbility::OnCompleteCallback);
	PlayHurtMontage->OnInterrupted.AddDynamic(this, &UMJGA_AIActionDamageAbility::OnInterruptedCallback);
	PlayHurtMontage->OnCancelled.AddDynamic(this, &UMJGA_AIActionDamageAbility::OnInterruptedCallback);

	PlayHurtMontage->ReadyForActivation();
}

void UMJGA_AIActionDamageAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_AIActionDamageAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	AMJCharacterBase* AMJCharacter = Cast<AMJCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!AMJCharacter)
	{
		return; 
	}

	// Minjin: Nav_Walking 이란 것이 있음
	AMJCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMJGA_AIActionDamageAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_AIActionDamageAbility::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_AIActionDamageAbility::OnBlendOutCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
