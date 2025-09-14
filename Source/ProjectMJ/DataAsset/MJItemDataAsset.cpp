// ThenOneDayStudio


#include "DataAsset/MJItemDataAsset.h"

UMJItemDataAsset::UMJItemDataAsset()
{
}

TSubclassOf<AMJItemBase> UMJItemDataAsset::FindItemClassForTag(const FGameplayTag& Tag) const
{
	if (const TSubclassOf<AMJItemBase>* FoundClass = ItemMap.Find(Tag))
	{
		return *FoundClass;
	}
	return nullptr;
}
