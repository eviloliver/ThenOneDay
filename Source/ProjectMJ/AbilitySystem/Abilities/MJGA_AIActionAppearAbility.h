// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_ActionAppearanceAbility.h"
#include "MJGA_AIActionAppearAbility.generated.h"

/**
 * Class Description: 적 등장
 * Author: Kim Minjin
 * Created Date: 2025.08.08.
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJGA_AIActionAppearAbility : public UMJGA_ActionAppearanceAbility
{
	GENERATED_BODY()

public:
	UMJGA_AIActionAppearAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:

	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();
};
