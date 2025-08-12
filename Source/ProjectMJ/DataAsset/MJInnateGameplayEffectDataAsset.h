// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MJInnateGameplayEffectDataAsset.generated.h"

class UGameplayEffect;
/**
 * Class Description: 시작 시 부여할 Effect
 * Author: 신동민
 * Created Date: 2025.08.12
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJInnateGameplayEffectDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UMJInnateGameplayEffectDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayEffect>> Effects;

};
