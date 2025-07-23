// ThenOneDayStudio


#include "TG/UI/MJNewGamePopUpWidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/Struct/MJSaveGame.h"


void UMJNewGamePopUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackButton->OnClicked.AddDynamic(this, &UMJNewGamePopUpWidget::OnClicked_BackButton);
	ConfirmButton->OnClicked.AddDynamic(this, &UMJNewGamePopUpWidget::OnClicked_ConfirmButton);
	
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
	
		return;
	}
	
	int8 NextSlotNum = GetEmptySlotNum();

	if (NextSlotNum == -1)
	{
		
	}
	else
	{
		UMJSaveGame* NewSave = Cast<UMJSaveGame>(UGameplayStatics::CreateSaveGameObject(UMJSaveGame::StaticClass()));
		NewSave->SlotNum = NextSlotNum;
		NewSave->PlayerName = InputPlayerNameTextBox->GetText().ToString();
		NewSave->SaveGameCreatedDateTime = FDateTime::Now();
		NewSave->RecentPlayedDateTime = FDateTime::Now();
		
		const FString SlotName = FString::Printf(TEXT("Slot_%d"), NextSlotNum);
		
		UGameplayStatics::SaveGameToSlot(NewSave, SlotName, 0);
	}

	UMJGameInstanceTG* MJGI = GetGameInstance<UMJGameInstanceTG>();
	if (MJGI)
	{
		MJGI->GetPlayerSessionDataRef().PlayerName = InputPlayerNameTextBox->GetText().ToString();
		MJGI->GetPlayerSessionDataRef().SaveGameSlotNum = NextSlotNum;
	}
	
	
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FInputModeGameAndUI InputModeGameAndUI;
		PC->SetInputMode(InputModeGameAndUI);
	}
	
	//OpenLevel
	
	UGameplayStatics::OpenLevel(this,TEXT("TG_Town"));
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
