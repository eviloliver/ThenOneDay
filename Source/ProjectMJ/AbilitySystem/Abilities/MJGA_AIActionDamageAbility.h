// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_ActionDamageAbility.h"
#include "MJGA_AIActionDamageAbility.generated.h"

/**
 * Class Description: 적 데미지 입음
 * Author: Kim Minjin
 * Created Date: 2025.08.28.
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJGA_AIActionDamageAbility : public UMJGA_ActionDamageAbility
{
	GENERATED_BODY()

public:
	UMJGA_AIActionDamageAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:

	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();

	UFUNCTION()
	void OnBlendOutCallback();
};
