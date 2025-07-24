// ThenOneDayStudio


#include "TG/UI/MJLoadGameSlotWidget.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "TG/SubSystem/MJSaveGameSubsystem.h"


void UMJLoadGameSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SlotNum = -1;
}

void UMJLoadGameSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UMJLoadGameSlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	UMJSaveGameSubsystem* SGSS = GetGameInstance()->GetSubsystem<UMJSaveGameSubsystem>();
	if (SGSS)
	{
		SGSS->LoadGameFromSlotNum(SlotNum);
		
		UGameplayStatics::OpenLevel(this,TEXT("TG_Town"));
	
		return FReply::Handled();
	}

	return FReply::Unhandled();
	
}

void UMJLoadGameSlotWidget::SetText(const FText NewSlotNumberText, const FText NewPlayerNameText, const FText NewCreatedDateText,
                                    const FText NewRecentPlayedDateText)
{
	SlotNumberText->SetText(NewSlotNumberText);
	PlayerNameText->SetText(NewPlayerNameText);
	CreatedDateText->SetText(NewCreatedDateText);
	RecentPlayedDateText->SetText(NewRecentPlayedDateText);
}

void UMJLoadGameSlotWidget::SetSlotNum(int8 InputSlotNum)
{
	SlotNum = InputSlotNum;
}

int8 UMJLoadGameSlotWidget::GetSlotNum()
{
	return SlotNum;
}

