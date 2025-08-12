// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_AIActionDeathAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/MJCharacterBase.h"
#include "MJ/Character/MJMonsterCharacter.h"

UMJGA_AIActionDeathAbility::UMJGA_AIActionDeathAbility()
{
}

void UMJGA_AIActionDeathAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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
	
	AMJCharacter->SetActorEnableCollision(false);
	
	UAbilityTask_PlayMontageAndWait* PlayDeathMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayDeath"), DeathActionAnimMontage, 1.0f);

	PlayDeathMontage->OnCompleted.AddDynamic(this, &UMJGA_AIActionDeathAbility::OnCompleteCallback);
	PlayDeathMontage->OnCancelled.AddDynamic(this, &UMJGA_AIActionDeathAbility::OnInterruptedCallback);
	PlayDeathMontage->OnBlendOut.AddDynamic(this, &UMJGA_AIActionDeathAbility::OnBlendOutCallback);

	PlayDeathMontage->ReadyForActivation();
}

void UMJGA_AIActionDeathAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_AIActionDeathAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	AMJCharacterBase* AMJCharacter = Cast<AMJCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!AMJCharacter)
	{
		return; 
	}

	AMJMonsterCharacter* Enemy = Cast<AMJMonsterCharacter>(AMJCharacter);
	if (Enemy)
	{
		// Minjin: 경험치 전달, 아이템 드랍
		Enemy->GiveDeathRewardTo();
	}
	
	// Minjin: Super에서 Destroy
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMJGA_AIActionDeathAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_AIActionDeathAbility::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_AIActionDeathAbility::OnBlendOutCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
