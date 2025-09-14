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
