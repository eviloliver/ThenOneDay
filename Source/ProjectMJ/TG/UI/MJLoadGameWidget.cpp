// ThenOneDayStudio


#include "TG/UI/MJLoadGameWidget.h"

#include "MJLoadGameSlotWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "TG/Struct/MJSaveGame.h"

void UMJLoadGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	BackButton->OnClicked.AddDynamic(this, &UMJLoadGameWidget::OnClicked_Back);

	SavedGameSlotScrollBox->ClearChildren();
	
	for (int i = 0; i < INT8_MAX; ++i)
	{
		const FString SlotName = FString::Printf(TEXT("Slot_%d"), i);
		if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		{
			UMJSaveGame* SaveGame = Cast<UMJSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
			if (SaveGame)
			{
				UMJLoadGameSlotWidget* NewSlotWidget = CreateWidget<UMJLoadGameSlotWidget>(this, LoadGameSlotWidgetClass);
				NewSlotWidget->SetText(FText::FromString(SaveGame->PlayerName),
					FText::FromString(SaveGame->SaveGameCreatedDateTime.ToString(TEXT("%Y/%m/%d %H:%M"))),
					FText::FromString(SaveGame->RecentPlayedDateTime.ToString(TEXT("%Y/%m/%d %H:%M")))
					
				);
				
				NewSlotWidget->SetSlotNum(SaveGame->SlotNum);
				
				SavedGameSlotScrollBox->AddChild(NewSlotWidget);
			}
		}
	}	
}

void UMJLoadGameWidget::OnClicked_Back()
{
	BackToParentWidget();
}

