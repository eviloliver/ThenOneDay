// ThenOneDayStudio


#include "TG/UI/MJNewGamePopUpWidget.h"

#include "ProjectMJ.h"
#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "TG/MJGameInstance.h"
#include "TG/Struct/MJSaveGame.h"


void UMJNewGamePopUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackButton->OnClicked.AddDynamic(this, &UMJNewGamePopUpWidget::OnClicked_BackButton);
	ConfirmButton->OnClicked.AddDynamic(this, &UMJNewGamePopUpWidget::OnClicked_ConfirmButton);

	NextSlotNum = -1; 
	
}

void UMJNewGamePopUpWidget::OnClicked_BackButton()
{
	BackToParentWidget();
}

void UMJNewGamePopUpWidget::OnClicked_ConfirmButton()
{
	if (InputPlayerNameTextBox->GetText().IsEmpty())
	{
		InputPlayerNameTextBox->SetHintText(FText::FromString(TEXT("Please Enter Valid Player Name!!")));

		UGameplayStatics::SpawnSound2D(GetWorld(),FailSound);
		return;
	}
	
	bool bHasValidSlot = (NextSlotNum = GetEmptySlotNum()) != -1;
	
	if (bHasValidSlot)
	{
		UMJSaveGame* NewSave = Cast<UMJSaveGame>(UGameplayStatics::CreateSaveGameObject(UMJSaveGame::StaticClass()));
		NewSave->SlotNum = NextSlotNum;
		NewSave->PlayerName = InputPlayerNameTextBox->GetText().ToString();
		NewSave->SaveGameCreatedDateTime = FDateTime::Now();
		NewSave->RecentPlayedDateTime = FDateTime::Now();
		
		const FString SlotName = FString::Printf(TEXT("Slot_%d"), NextSlotNum);
		
		UGameplayStatics::SaveGameToSlot(NewSave, SlotName, 0);
	}
	else
	{
		InputPlayerNameTextBox->SetHintText(FText::FromString(TEXT("### Has No Valid Slot!! ###")));
	}

	// Switch to InGame When sound play end
	// UAudioComponent* AudioComp = UGameplayStatics::SpawnSound2D(GetWorld(),SuccessSound);
	// if (AudioComp)
	// {
	// 	AudioComp->OnAudioFinished.AddDynamic(this, &UMJNewGamePopUpWidget::SwitchToInGame);
	// }
	SwitchToInGame();
}

void UMJNewGamePopUpWidget::SwitchToInGame()
{
	UMJGameInstance* MJGI = GetGameInstance<UMJGameInstance>();
	if (MJGI)
	{
		MJGI->GetPlayerSessionDataRef().PlayerName = InputPlayerNameTextBox->GetText().ToString();
		MJGI->GetPlayerSessionDataRef().SaveGameSlotNum = NextSlotNum;
	}
	
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FInputModeGameAndUI InputModeGameAndUI;
		InputModeGameAndUI.SetHideCursorDuringCapture(false);
		PC->SetInputMode(InputModeGameAndUI);
	}
	// OpenLevel
	
	UGameplayStatics::OpenLevel(this,MAP_TOWN);
}

int8 UMJNewGamePopUpWidget::GetEmptySlotNum()
{
	for (int8 i = 0; i < INT8_MAX; ++i)
	{
		const FString SlotName = FString::Printf(TEXT("Slot_%d"), i);
		if (!UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		{
			return i;
		}
	}
	return -1;
}
