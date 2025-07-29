// ThenOneDayStudio


#include "MJ/DataAssetMJ/MJDropItemsDataAsset.h"

#include "ProjectMJ.h"
#include "Kismet/KismetMathLibrary.h"
#include "TG/MJGameInstanceTG.h"
#include "UI/Inventory/ItemDataRow.h"
#include "Item/MJItemBase.h"

UMJDropItemsDataAsset::UMJDropItemsDataAsset()
{
}

FGameplayTag UMJDropItemsDataAsset::TryDropItem() const
{
	// Minjin: 아이템 배열 중 랜덤한 아이템 선택, 확률 적용해 드랍할지 말지 정함
	if(DropItems.IsEmpty())
	{
		return FGameplayTag::EmptyTag;
	}

	int32 IndexRamge = DropItems.Num()-1;

	int32 RandIndex = UKismetMathLibrary::RandomIntegerInRange(0, IndexRamge);

	FGameplayTag ItemTag = DropItems[RandIndex].ItemTag;

	bool IsCanDrop = UKismetMathLibrary::RandomBoolWithWeight(DropItems[RandIndex].DropChance);

	if (IsCanDrop)
	{
		return ItemTag;
	}
	
	return FGameplayTag::EmptyTag;
}

TSubclassOf<AMJItemBase> UMJDropItemsDataAsset::FindItemClassForTag(const FGameplayTag& ItemTag) const
{
	// if (!ItemTag.IsValid())
	// {
	// 	return nullptr;
	// }
	// UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
	// if (!GI || !GI->ItemDataTable)
	// {
	// 	MJ_LOG(LogMJ, Error, TEXT("Not Exist GI or ItemDataTable"));
	// 	return nullptr;
	// }
	//
	// const FItemDataRow* DataRow = GI->ItemDataTable->FindRow<FItemDataRow>(ItemTag.GetTagName(), TEXT("Find ItemDataTable"));
	// if (!DataRow)
	// {
	// 	MJ_LOG(LogMJ, Error, TEXT("Not Exist DataRow"));
	// 	return nullptr;
	// }
	//
	// TSubclassOf<AMJItemBase> ItemClass = * DataRow->ItemClass;
	// if (ItemClass == nullptr)
	// {
	// 	return nullptr;
	// }
	//
	// return ItemClass;
	return nullptr;
}
