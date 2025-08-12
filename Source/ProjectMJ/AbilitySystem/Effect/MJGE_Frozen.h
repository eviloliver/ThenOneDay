// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "MJGE_Frozen.generated.h"

/**
 * Class Description: 동상 상태이상 - 느려짐(Skill에서 StatusEffectSlowPercent 값 설정 필요)
 * Author: Kim Minjin
 * Created Date: 2025.08.12.
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJGE_Frozen : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UMJGE_Frozen();
};
