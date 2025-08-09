// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_PlayerActionAppearAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/MJCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UMJGA_PlayerActionAppearAbility::UMJGA_PlayerActionAppearAbility()
{
}

void UMJGA_PlayerActionAppearAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (AppearanceActionAnimMontage == nullptr)
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
	
	UAbilityTask_PlayMontageAndWait* PlayDeathMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), AppearanceActionAnimMontage, 1.0f);

	PlayDeathMontage->OnCompleted.AddDynamic(this, &UMJGA_PlayerActionAppearAbility::OnCompleteCallback);
	PlayDeathMontage->OnInterrupted.AddDynamic(this, &UMJGA_PlayerActionAppearAbility::OnInterruptedCallback);
	PlayDeathMontage->OnCancelled.AddDynamic(this, &UMJGA_PlayerActionAppearAbility::OnInterruptedCallback);
	PlayDeathMontage->OnBlendOut.AddDynamic(this, &UMJGA_PlayerActionAppearAbility::OnBlendOutCallback);

	PlayDeathMontage->ReadyForActivation();
}

void UMJGA_PlayerActionAppearAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_PlayerActionAppearAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AMJCharacterBase* AMJCharacter = Cast<AMJCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!AMJCharacter)
	{
		return; 
	}
	AMJCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void UMJGA_PlayerActionAppearAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_PlayerActionAppearAbility::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_PlayerActionAppearAbility::OnBlendOutCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
