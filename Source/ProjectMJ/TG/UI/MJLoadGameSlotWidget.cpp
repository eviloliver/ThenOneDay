// ThenOneDayStudio


#include "TG/UI/MJLoadGameSlotWidget.h"

#include "Components/AudioComponent.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
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
		bool bLoadSlotSucceeded  = SGSS->LoadGameFromSlotNum(SlotNum);
		
		if (bLoadSlotSucceeded)
		{
			// UAudioComponent* AudioComp = UGameplayStatics::SpawnSound2D(GetWorld(),SuccessSound);
			// if (AudioComp)
			// {
			// 	AudioComp->OnAudioFinished.AddDynamic(this, &UMJLoadGameSlotWidget::SwitchToInGame);
			// }
			SwitchToInGame();
			return FReply::Handled();
		}
	}
	
	UGameplayStatics::SpawnSound2D(GetWorld(),FailSound);
	
	return FReply::Unhandled();
}

void UMJLoadGameSlotWidget::SwitchToInGame()
{
	UGameplayStatics::OpenLevel(this,TEXT("TG_Town"));
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

