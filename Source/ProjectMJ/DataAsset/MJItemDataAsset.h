// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MJItemDataAsset.generated.h"

class AMJItemBase;
/**
 * Class Description: 아이템 태그로 실제 아이템 클래스 매핑하는 데이터 에셋
 * Author: Kim Minjin
 * Created Date: 2025.07.26.
 * Last Modified By:
 * Last Modified Date: 현재 사용 안 함.(DropItemsDataAsset 사용)
 */
UCLASS()
class PROJECTMJ_API UMJItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UMJItemDataAsset();
	
	TSubclassOf<AMJItemBase> FindItemClassForTag(const FGameplayTag& Tag) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (Categories = "Item"))
	TMap<FGameplayTag, TSubclassOf<AMJItemBase>> ItemMap;
};
