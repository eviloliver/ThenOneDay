// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "MJGA_ActionDeathAbility.generated.h"

/**
 * Class Description: Death Ability
 * Author: Kim Minjin
 * Created Date: 2025.08.08.
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJGA_ActionDeathAbility : public UMJGA_GameplayAbility
{
	GENERATED_BODY()

public:
	UMJGA_ActionDeathAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathActionAnimMontage;
};
