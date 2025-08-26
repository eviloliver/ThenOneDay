// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MJStateAbilityDataAsset.generated.h"

class UGameplayAbility;
/**
 * Class Description: 시작 시 부여할 State에 관련된 Ability의 데이터에셋.
 * Author: Kim Minjin
 * Created Date: 2025.08.08.
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJStateAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UMJStateAbilityDataAsset(){};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> ActionAppearanceAbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> ActionDamageAbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> ActionDeathAbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayAbility>> StateAbilityClasses;
};
