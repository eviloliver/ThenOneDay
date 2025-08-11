// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_ActionDamageAbility.h"

#include "ProjectMJ.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/MJCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UMJGA_ActionDamageAbility::UMJGA_ActionDamageAbility()
{
}

void UMJGA_ActionDamageAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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

	PlayHurtMontage->OnCompleted.AddDynamic(this, &UMJGA_ActionDamageAbility::OnCompleteCallback);
	PlayHurtMontage->OnInterrupted.AddDynamic(this, &UMJGA_ActionDamageAbility::OnInterruptedCallback);
	PlayHurtMontage->OnCancelled.AddDynamic(this, &UMJGA_ActionDamageAbility::OnInterruptedCallback);

	PlayHurtMontage->ReadyForActivation();
}

void UMJGA_ActionDamageAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_ActionDamageAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AMJCharacterBase* AMJCharacter = Cast<AMJCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!AMJCharacter)
	{
		return; 
	}

	// Minjin: Nav_Walking 이란 것이 있음
	AMJCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void UMJGA_ActionDamageAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_ActionDamageAbility::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
