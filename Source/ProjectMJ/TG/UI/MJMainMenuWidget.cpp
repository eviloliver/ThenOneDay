// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/UI/MJMainMenuWidget.h"

#include "MJGameFlowPopUpMsgWidget.h"
#include "MJSettingsWidget.h"
#include "ProjectMJ.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TG/SubSystem/MJSaveGameSubsystem.h"


void UMJMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_NewGame->OnClicked.AddDynamic(this, &ThisClass::OnClicked_NewGame);
	Button_Tutorial->OnClicked.AddDynamic(this, &ThisClass::OnClicked_Tutorial);
	Button_LoadGame->OnClicked.AddDynamic(this, &ThisClass::OnClicked_LoadGame);
	Button_Settings->OnClicked.AddDynamic(this, &ThisClass::OnClicked_Settings);
	Button_Quit->OnClicked.AddDynamic(this, &ThisClass::OnClicked_Quit);
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(this->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		InputMode.SetHideCursorDuringCapture(false);
		
		PC->SetInputMode(InputMode);
		PC->SetShowMouseCursor(true);

		NewGamePopUpWidget = Cast<UMJChildMenuBaseWidget>(CreateWidget(PC, NewGamePopUpWidgetClass));
		if (NewGamePopUpWidget)
		{
			NewGamePopUpWidget->AddToViewport(2);
			NewGamePopUpWidget->SetParentWidget(this);
			NewGamePopUpWidget->SetVisibility(ESlateVisibility::Hidden);
		}

		LoadGameWidget =  Cast<UMJChildMenuBaseWidget>(CreateWidget(PC,LoadGameWidgetClass));
		if (LoadGameWidget)
		{
			LoadGameWidget->AddToViewport(2);
			LoadGameWidget->SetParentWidget(this);
			LoadGameWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		
		SettingsWidget =  Cast<UMJChildMenuBaseWidget>(CreateWidget(PC,SettingsWidgetClass));
		if (SettingsWidget)
		{
			SettingsWidget->AddToViewport(2);
			SettingsWidget->SetParentWidget(this);
			SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		
		PopUpMsgWidget = Cast<UMJChildMenuBaseWidget>(CreateWidget(PC,PopUpMsgWidgetClass));
		if (PopUpMsgWidget)
		{
			PopUpMsgWidget->AddToViewport(2);
			PopUpMsgWidget->SetParentWidget(this);
			PopUpMsgWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UMJMainMenuWidget::OnClicked_NewGame()
{
	if (GetGameInstance()->GetSubsystem<UMJSaveGameSubsystem>()->IsSlotFull())
	{
		UMJGameFlowPopUpMsgWidget* CastedWidget = Cast<UMJGameFlowPopUpMsgWidget>(PopUpMsgWidget);
		
		if (CastedWidget)
		{
			TWeakObjectPtr<UMJMainMenuWidget> WeakThis = this;
			CastedWidget->PopUpWithCallback(FOnUserConfirmed::CreateLambda([WeakThis]
			{
				if (WeakThis.IsValid())
				{
					WeakThis->PopUpMsgWidget->BackToParentWidget();
				}
			}), FText::FromString(TEXT("All slots are full! Please delete at least one slot.")));
		}
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
		NewGamePopUpWidget->SetVisibility(ESlateVisibility::Visible);

	}
}

void UMJMainMenuWidget::OnClicked_Tutorial()
{
	SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::OpenLevel(this,MAP_Tutorial);
}

void UMJMainMenuWidget::OnClicked_LoadGame()
{
	SetVisibility(ESlateVisibility::Hidden);

	if (LoadGameWidget)
	{
		LoadGameWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMJMainMenuWidget::OnClicked_Settings()
{
	SetVisibility(ESlateVisibility::Hidden);
	
	if (SettingsWidget)
	{
		SettingsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMJMainMenuWidget::OnClicked_Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),nullptr,EQuitPreference::Quit,false);
}
