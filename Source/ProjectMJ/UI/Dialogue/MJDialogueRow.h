#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MJDialogueRow.generated.h"
/**
 * Class Description: DataTable 항목 구조체
 * Author: 이지수
 * Created Date: 2025.06.12
 * Last Modified By: 이지수
 * Last Modified Date: 2025.06.12
 */
USTRUCT(BlueprintType)
struct FMJDialogueRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;
};
