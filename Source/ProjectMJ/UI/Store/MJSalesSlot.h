// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJStoreSlotBase.h"
#include "Components/TextBlock.h"
#include "MJSalesSlot.generated.h"

/**
* Class Description: 스토어 위젯의 내 아이템창 슬롯
 * Author: 이지수
 * Created Date: 2025.08.09
 * Last Modified By: 
 * Last Modified Date: 
 */

UCLASS()
class PROJECTMJ_API UMJSalesSlot : public UMJStoreSlotBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Count;
	
public:
	void SetCount(int32 count);

};
