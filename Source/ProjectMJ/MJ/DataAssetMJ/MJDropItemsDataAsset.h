// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MJDropItemsDataAsset.generated.h"

/**
 * Class Description: Enemy가 가지고 있는 아이템에 대한 데이터에셋.
 * Author: Kim Minjin
 * Created Date: 2025.07.29.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */

class AMJItemBase;

USTRUCT(BlueprintType)
struct FDropItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories = "Item"))
	FGameplayTag ItemTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0", Delta = "0.01", DisplayName = "Drop Chance (%)"))
	float DropChance;	// 0.0f ~ 1.0f;
	// Required Condition // 아이템을 얻을 수 있는 조건(퀘스트 등)
};

UCLASS()
class PROJECTMJ_API UMJDropItemsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UMJDropItemsDataAsset();
	
	FGameplayTag TryDropItem() const;
	
protected:
	UPROPERTY(EditAnywhere)
	TArray<FDropItemInfo> DropItems;
};
