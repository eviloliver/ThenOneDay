// ThenOneDayStudio


#include "TG/UI/MJLoadGameSlotWidget.h"

#include "MJGameFlowHUDWidget.h"
#include "MJLoadGameWidget.h"
#include "ProjectMJ.h"
#include "Components/AudioComponent.h"
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
}

FReply UMJLoadGameSlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UMJSaveGameSubsystem* SGSS = GetGameInstance()->GetSubsystem<UMJSaveGameSubsystem>();
	if (SGSS)
	{

		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == MAP_TOWN)
		{
			// Saving at SavePoint. Widget popups only in town.
			
			GetGameInstance()->GetSubsystem<UMJSaveGameSubsystem>()->SaveGameToSelectedSlotNum(SlotNum);
			
			AMJPlayerController* MJPC = Cast<AMJPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
			if (MJPC)
			{
				MJPC->GetGameFlowHUD()->GetSaveGameWidget()->SetVisibility(ESlateVisibility::Hidden);
				MJPC->ChangeToIMCDefault();
			}
		}
		else
		{
			bool bLoadSlotSucceeded  = SGSS->LoadGameFromSlotNum(SlotNum);
		
			if (bLoadSlotSucceeded)
			{
				// UAudioComponent* AudioComp = UGameplayStatics::SpawnSound2D(GetWorld(),SuccessSound);
				// if (AudioComp)
				// {
				// 	AudioComp->OnAudioFinished.AddDynamic(this, &UMJLoadGameSlotWidget::SwitchToInGame);
				// }
				
				SwitchToInGame();
			}
			
		}
		return FReply::Handled();
	}
	
	UGameplayStatics::SpawnSound2D(GetWorld(),FailSound);
	
	return FReply::Unhandled();
}

void UMJLoadGameSlotWidget::SwitchToInGame()
{
	UGameplayStatics::OpenLevel(this,MAP_TOWN);
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

