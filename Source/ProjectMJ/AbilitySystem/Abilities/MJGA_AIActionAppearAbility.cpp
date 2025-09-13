// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_AIActionAppearAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Character/MJCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UMJGA_AIActionAppearAbility::UMJGA_AIActionAppearAbility()
{
}

void UMJGA_AIActionAppearAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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

	AMJCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);

	// Minjin: IsInactivated 태그 제거 - 활성화
	const FGameplayTag InActivatedTag = FGameplayTag::RequestGameplayTag(TEXT("Character.State.IsInactivated"));
	AMJCharacter->ASC->RemoveLooseGameplayTag(InActivatedTag);
	
	UAbilityTask_PlayMontageAndWait* PlayAppearMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy
	(this, TEXT("PlayAppear"), AppearanceActionAnimMontage, 1.0f);

	PlayAppearMontage->OnCompleted.AddDynamic(this, &UMJGA_AIActionAppearAbility::OnCompleteCallback);
	PlayAppearMontage->OnInterrupted.AddDynamic(this, &UMJGA_AIActionAppearAbility::OnInterruptedCallback);
	PlayAppearMontage->OnCancelled.AddDynamic(this, &UMJGA_AIActionAppearAbility::OnInterruptedCallback);
	PlayAppearMontage->OnBlendOut.AddDynamic(this, &UMJGA_AIActionAppearAbility::OnBlendOutCallback);

	PlayAppearMontage->ReadyForActivation();
}

void UMJGA_AIActionAppearAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_AIActionAppearAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
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

void UMJGA_AIActionAppearAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);

}

void UMJGA_AIActionAppearAbility::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);

}

void UMJGA_AIActionAppearAbility::OnBlendOutCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
