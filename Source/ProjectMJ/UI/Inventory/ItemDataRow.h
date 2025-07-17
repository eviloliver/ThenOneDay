#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "ItemDataRow.generated.h"
/**
 * Class Description: Item DataTable Base
 * Author: 이지수
 * Created Date: ?
 * Last Modified By: 이지수
 * Last Modified Date: 2025.07.15 / Add 
 */
UENUM(BlueprintType)
enum class EItemType : uint8
{
	None		UMETA(DisplayName = "None"),
	Weapon		UMETA(DisplayName = "Weapon"),
	Armor		UMETA(DisplayName = "Armor"),
	Consumable	UMETA(DisplayName = "Consumable"),
	Material	UMETA(DisplayName = "Material"),
	Quest		UMETA(DisplayName = "Quest")
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common		UMETA(DisplayName = "Common"),
	Uncommon	UMETA(DisplayName = "Uncommon"),
	Rare        UMETA(DisplayName = "Rare"),
	Epic        UMETA(DisplayName = "Epic"),
	Legendary   UMETA(DisplayName = "Legendary")
};

USTRUCT(BlueprintType) 
struct FItemDataRow : public FTableRowBase // 안바뀌는값 // 아이템 고유 정보
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag DropMonsterTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity Rarity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMerchandise;


};
