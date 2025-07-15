#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataRow.generated.h"

USTRUCT(BlueprintType) 
struct FItemDataRow : public FTableRowBase // 안바뀌는값 // 아이템 고유 정보
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMerchandise;
	
};
