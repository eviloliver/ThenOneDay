// ThenOneDayStudio


#include "TG/UI/MJLoadGameSlotWidget.h"

#include "MJGameFlowHUDWidget.h"
#include "MJGameFlowPopUpMsgWidget.h"
#include "MJLoadGameWidget.h"
#include "ProjectMJ.h"
#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Controller/MJPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "TG/SubSystem/MJSaveGameSubsystem.h"


void UMJLoadGameSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SlotNum = -1;
}

void UMJLoadGameSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DeleteButton->OnClicked.AddDynamic(this, &UMJLoadGameSlotWidget::DeleteSelf);
	
	PopUpMsgWidget = Cast<UMJGameFlowPopUpMsgWidget>(CreateWidget(this,PopUpMessageWidgetClass));
	if (PopUpMsgWidget)
	{
		PopUpMsgWidget->AddToViewport(3);
		PopUpMsgWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

FReply UMJLoadGameSlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UMJSaveGameSubsystem* SGSS = GetGameInstance()->GetSubsystem<UMJSaveGameSubsystem>();
	
	if (SGSS)
	{
		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == MAP_TOWN)
		{
			PopUpMsgWidget->SetVisibility(ESlateVisibility::Visible);
			
			TWeakObjectPtr<UMJLoadGameSlotWidget> WeakThis = this;
			PopUpMsgWidget->PopUpWithCallback(FOnUserConfirmed::CreateLambda([WeakThis]
				{
					// Saving at SavePoint. Widget popups only in town.
					if (WeakThis.IsValid())
					{
						WeakThis->GetGameInstance()->GetSubsystem<UMJSaveGameSubsystem>()->SaveGameToSelectedSlotNum(WeakThis->SlotNum);
							
						AMJPlayerController* MJPC = Cast<AMJPlayerController>(UGameplayStatics::GetPlayerController(WeakThis->GetWorld(),0));
							
						if (MJPC)
						{
							MJPC->GetGameFlowHUD()->GetSaveGameWidget()->SetVisibility(ESlateVisibility::Hidden);
							MJPC->ChangeToIMCDefault();
						}
					
						UGameplayStatics::SpawnSound2D(WeakThis->GetWorld(),WeakThis->FailSound);
					}

				}), FText::FromString(FString::Printf(TEXT("Are you sure to Save at Slot_%d ?"), SlotNum) ));
		}
		else if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == MAP_MAINMENU)
		{
			bool bLoadSlotSucceeded  = SGSS->LoadGameFromSlotNum(SlotNum);
		
			if (bLoadSlotSucceeded)
			{
				UGameplayStatics::SpawnSound2D(GetWorld(),FailSound);
				SwitchToInGame();
			}
		}
	}
	
	return FReply::Handled();
}

void UMJLoadGameSlotWidget::SwitchToInGame()
{
	UGameplayStatics::OpenLevel(this,MAP_TOWN);
}

void UMJLoadGameSlotWidget::DeleteSelf()
{
	
	bool bDeleted = UGameplayStatics::DeleteGameInSlot("Slot_" + FString::FromInt(SlotNum),0);

	if (bDeleted)
	{
		RemoveFromParent();	
	}
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

