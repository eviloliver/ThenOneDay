#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryItemData.generated.h"

USTRUCT(BlueprintType) 
struct FInventoryItemData : public FTableRowBase // 안바뀌는값
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
};
