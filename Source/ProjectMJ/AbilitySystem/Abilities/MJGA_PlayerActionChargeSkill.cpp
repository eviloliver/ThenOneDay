// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_PlayerActionChargeSkill.h"

#include "MJGA_PlayerActionInstantSkill.h"
#include "AbilitySystem/AbilityTasks/MJAT_GetMousePosition.h"

UMJGA_PlayerActionChargeSkill::UMJGA_PlayerActionChargeSkill()
{
}

void UMJGA_PlayerActionChargeSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UMJAT_GetMousePosition* GetMousePositionTask = UMJAT_GetMousePosition::CreateTask(this);
	GetMousePositionTask->OnCompleted.AddDynamic(this, &UMJGA_PlayerActionChargeSkill::OnMousePositionReady);
	GetMousePositionTask->OnFailed.AddDynamic(this, &UMJGA_PlayerActionChargeSkill::OnMousePositionFailed);

	GetMousePositionTask->ReadyForActivation();
}

void UMJGA_PlayerActionChargeSkill::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_PlayerActionChargeSkill::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                                  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void UMJGA_PlayerActionChargeSkill::OnMousePositionReady(const FVector& MouseLocation)
{
}

void UMJGA_PlayerActionChargeSkill::OnMousePositionFailed(const FVector& IgnoreLocation)
{
}

void UMJGA_PlayerActionChargeSkill::OnCompleteCallback()
{
}

void UMJGA_PlayerActionChargeSkill::OnInterruptedCallback()
{
}
