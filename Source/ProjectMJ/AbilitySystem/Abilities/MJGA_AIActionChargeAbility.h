// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_ChargeSkill.h"
#include "MJGA_AIActionChargeAbility.generated.h"

/**
 * Class Description: AI 전용 Charge 스킬
 * Author: 신동민
 * Created Date: 2025.08.09
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJGA_AIActionChargeAbility : public UMJGA_ChargeSkill
{
	GENERATED_BODY()

public:
	UMJGA_AIActionChargeAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	UFUNCTION()
	void OnChargeDelayFinished();

	UFUNCTION()
	void OnReleaseMontageComplete();

	void PlayReleaseMontage();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeTime;

};
