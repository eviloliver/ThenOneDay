// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_ChargeSkill.h"
#include "MJGA_PlayerActionChargeSkill.generated.h"

/**
 * Class Description: 플레이어의 Charge 스킬
 * Author: 신동민
 * Created Date: 2025.08.06
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJGA_PlayerActionChargeSkill : public UMJGA_ChargeSkill
{
	GENERATED_BODY()
public:
	UMJGA_PlayerActionChargeSkill();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UFUNCTION()
	void OnMousePositionReady(const FVector& MouseLocation);

	UFUNCTION()
	void OnMousePositionFailed(const FVector& IgnoreLocation);

	UFUNCTION()
	void OnReleaseMontageComplete();

	void PlayReleaseMontage();
};
