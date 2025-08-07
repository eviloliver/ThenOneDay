// ThenOneDayStudio


#include "TG/UI/MJLoadGameWidget.h"

#include "MJLoadGameSlotWidget.h"
#include "ProjectMJ.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Controller/MJPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TG/Struct/MJSaveGame.h"



void UMJLoadGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MaxSlotNum = 8;
	
	BackButton->OnClicked.AddDynamic(this, &UMJLoadGameWidget::OnClicked_Back);

	SavedGameSlotScrollBox->ClearChildren();

	BackGround->SetVisibility(ESlateVisibility::Visible);
	

	InitializeSlot();
}

void UMJLoadGameWidget::InitializeSlot()
{
	for (int i = 0; i < MaxSlotNum; ++i)
    	{
    		const FString SlotName = FString::Printf(TEXT("Slot_%d"), i);
    		
    		if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
    		{
    			UMJSaveGame* SaveGame = Cast<UMJSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
    			if (SaveGame)
    			{
    				UMJLoadGameSlotWidget* NewSlotWidget = CreateWidget<UMJLoadGameSlotWidget>(this, LoadGameSlotWidgetClass);
    				if (NewSlotWidget)
    				{
    					NewSlotWidget->SetSlotNum(SaveGame->SlotNum);
    					NewSlotWidget->SetText(FText::FromString(FString::FromInt(SaveGame->SlotNum)),
							FText::FromString(SaveGame->PlayerName),
							FText::FromString(SaveGame->SaveGameCreatedDateTime.ToString(TEXT("%Y/%m/%d %H:%M"))),
							FText::FromString(SaveGame->RecentPlayedDateTime.ToString(TEXT("%Y/%m/%d %H:%M")))
						);
    				
    					NewSlotWidget->SetPadding(FMargin(20.0f,20.f,20.f,20.f));
    					SavedGameSlotScrollBox->AddChild(NewSlotWidget);
    				}
    			}
    		}
    		else
    		{
    			UMJLoadGameSlotWidget* NewSlotWidget = CreateWidget<UMJLoadGameSlotWidget>(this, LoadGameSlotWidgetClass);

    			if (NewSlotWidget)
    			{
    				NewSlotWidget->SetSlotNum(i);
    				NewSlotWidget->SetText(FText::FromString(FString::FromInt(i)),
    					FText::FromString(TEXT("Empty")),
    					FText(),
    					FText()
    				);
    				
    				NewSlotWidget->SetPadding(FMargin(20.0f,20.f,20.f,20.f));
    				SavedGameSlotScrollBox->AddChild(NewSlotWidget);
    			}
    		}
    	}	
}


void UMJLoadGameWidget::UpdateSlot()
{
	for (int i = 0; i < MaxSlotNum; ++i)
	{
		const FString SlotName = FString::Printf(TEXT("Slot_%d"), i);
		
		if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		{
			UMJSaveGame* SaveGame = Cast<UMJSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
			if (SaveGame)
			{
				UWidget* ChildWidget = SavedGameSlotScrollBox->GetChildAt(i);

				UMJLoadGameSlotWidget* ChildSlotWidget = Cast<UMJLoadGameSlotWidget>(ChildWidget);
				
				if (ChildSlotWidget)
				{
					ChildSlotWidget->SetSlotNum(SaveGame->SlotNum);
					ChildSlotWidget->SetText(FText::FromString(FString::FromInt(SaveGame->SlotNum)),
						FText::FromString(SaveGame->PlayerName),
						FText::FromString(SaveGame->SaveGameCreatedDateTime.ToString(TEXT("%Y/%m/%d %H:%M"))),
						FText::FromString(SaveGame->RecentPlayedDateTime.ToString(TEXT("%Y/%m/%d %H:%M")))
					);
					
					ChildSlotWidget->SetPadding(FMargin(20.0f,20.f,20.f,20.f));
				}
			}
		}
	}	
}

void UMJLoadGameWidget::OnClicked_Back()
{
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == MAP_TOWN)
	{
		SetVisibility(ESlateVisibility::Hidden);
		AMJPlayerController* MJPC = Cast<AMJPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
		if (MJPC)
		{
			MJPC->ChangeToIMCDefault();
		}
	}
	else
	{
		BackToParentWidget();
	}
}

