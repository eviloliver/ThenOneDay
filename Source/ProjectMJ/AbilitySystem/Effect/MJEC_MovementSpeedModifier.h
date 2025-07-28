// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "MJEC_MovementSpeedModifier.generated.h"

/**
 * Class Description: DOT  주기적인 피해를 계산하는 클래스
 * Author: 신동민
 * Created Date: 2025.07.28
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

UCLASS()
class PROJECTMJ_API UMJEC_MovementSpeedModifier : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UMJEC_MovementSpeedModifier();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
