// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "MJEC_StaminaRegen.generated.h"

/**
 * Class Description: 스태미너 재생 계산
 * Author: 신동민
 * Created Date: 2025.08.12
 * Description of Change:
 * Modified By:
 * Modified Date:
 */


UCLASS()
class PROJECTMJ_API UMJEC_StaminaRegen : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:

	UMJEC_StaminaRegen();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
