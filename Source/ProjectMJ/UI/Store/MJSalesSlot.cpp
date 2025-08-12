// ThenOneDayStudio


#include "UI/Store/MJSalesSlot.h"

#include "Components/TextBlock.h"

void UMJSalesSlot::SetCount(int32 count)
{
	this->Count->SetText(FText::FromString(FString::Printf(TEXT(" 판매 가능 수량 : %d"), count)));
}
