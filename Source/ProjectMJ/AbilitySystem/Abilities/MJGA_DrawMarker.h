// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "MJGA_DrawMarker.generated.h"

/**
 * Class Description: 플레이어의 Charge 스킬
 * Author: 신동민
 * Created Date: 2025.08.06
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

class UNiagaraSystem;

UCLASS()
class PROJECTMJ_API UMJGA_DrawMarker : public UMJGA_GameplayAbility
{
	GENERATED_BODY()

public:
	UMJGA_DrawMarker();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> NiagaraSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ZOffset = 1.5f;

};
