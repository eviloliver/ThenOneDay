// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/UI/MJPauseMenuWidget.h"

#include "MJGameFlowPopUpMsgWidget.h"
#include "ProjectMJ.h"
#include "Components/Button.h"
#include "Components/Spacer.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MJPlayerState.h"
#include "TG/GameMode/MJGameModeDungeon.h"
#include "TG/GameMode/MJGameModeTown.h"
#include "TG/SubSystem/MJSaveGameSubsystem.h"

void UMJPauseMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMJPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Resume->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_Resume);
	Button_Settings->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_Settings);
	Button_MainMenu->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_MainMenu);
	Button_GotoTown->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_GotoTown);
	Button_QuitGame->OnClicked.AddDynamic(this, &UMJPauseMenuWidget::OnClicked_QuitGame);

	if (PC.IsValid())
	{
		SettingsWidget = Cast<UMJChildMenuBaseWidget>(CreateWidget(this, SettingsWidgetClass));
		if (SettingsWidget)
		{		
			SettingsWidget->SetParentWidget(this);
			SettingsWidget->AddToViewport(2);
			SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
		}

		ForceExitCautionWidget = Cast<UMJChildMenuBaseWidget>(CreateWidget(this,ForceExitCautionWidgetClass));
		if (ForceExitCautionWidget)
		{
			ForceExitCautionWidget->SetParentWidget(this);
			ForceExitCautionWidget->AddToViewport(2);
			ForceExitCautionWidget->SetVisibility(ESlateVisibility::Hidden);
		}

		if (AMJGameModeTown* GMTown = GetWorld()->GetAuthGameMode<AMJGameModeTown>())
		{
			Button_GotoTown->SetVisibility(ESlateVisibility::Collapsed);
		}
		else if (AMJGameModeDungeon* GMDungeon = GetWorld()->GetAuthGameMode<AMJGameModeDungeon>())
		{
			Button_GotoTown->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UMJPauseMenuWidget::OnClicked_Resume()
{
	if (PC.IsValid())
	{
		SetVisibility(ESlateVisibility::Hidden);
			
		if (PC->IsPaused())
		{
			PC->SetPause(false);
		}		
	}
}

void UMJPauseMenuWidget::OnClicked_SaveGame()
{
	if (PC.IsValid())
	{
		AMJPlayerState* PS = PC->GetPlayerState<AMJPlayerState>();
		if (PS)
		{
			PS->SaveToInstancedPlayerSessionData();
			GetGameInstance()->GetSubsystem<UMJSaveGameSubsystem>()->SaveGameToCurrentSlotNum();
		}
	}
}

void UMJPauseMenuWidget::OnClicked_Settings()
{
	if (SettingsWidget)
	{
		SetVisibility(ESlateVisibility::Hidden);
		SettingsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMJPauseMenuWidget::OnClicked_MainMenu()
{
	if (PC.IsValid())
	{
		
		SetVisibility(ESlateVisibility::Hidden);
		UMJGameFlowPopUpMsgWidget* CastedWidget = Cast<UMJGameFlowPopUpMsgWidget>(ForceExitCautionWidget);
		
		if (CastedWidget)
		{
			TWeakObjectPtr<UMJPauseMenuWidget> WeakThis = this;
			CastedWidget->PopUpWithCallback(FOnUserConfirmed::CreateLambda([WeakThis]
			{
				if (WeakThis.IsValid())
				{
					AMJGameModeBase* MJGM = WeakThis->GetWorld()->GetAuthGameMode<AMJGameModeBase>();
					if (MJGM)
					{
						MJGM->TravelToMap(TEXT("TG_MainMenu"));
					}
				}
			}), FText::FromString(TEXT("All unsaved changes will be lost. Are you sure you want to go main menu?")));
		}
	}
}

void UMJPauseMenuWidget::OnClicked_GotoTown()
{
	if (PC.IsValid())
	{

		SetVisibility(ESlateVisibility::Hidden);
		UMJGameFlowPopUpMsgWidget* CastedWidget = Cast<UMJGameFlowPopUpMsgWidget>(ForceExitCautionWidget);
		
		if (CastedWidget)
		{
			TWeakObjectPtr<UMJPauseMenuWidget> WeakThis = this;
			CastedWidget->PopUpWithCallback(FOnUserConfirmed::CreateLambda([WeakThis]
			{
				if (WeakThis.IsValid())
				{
					AMJGameModeBase* MJGM = WeakThis->GetWorld()->GetAuthGameMode<AMJGameModeBase>();
					if (MJGM)
					{
						MJGM->TravelToMap(MAP_TOWN);
					}
				}
			}), FText::FromString(TEXT("All unsaved changes will be lost. Are you sure you want to go back to town?")));
		}
		
	}
}

void UMJPauseMenuWidget::OnClicked_QuitGame()
{
	if (IsValid(ForceExitCautionWidget))
	{
		SetVisibility(ESlateVisibility::Hidden);
		UMJGameFlowPopUpMsgWidget* CastedWidget = Cast<UMJGameFlowPopUpMsgWidget>(ForceExitCautionWidget);
		
		if (CastedWidget)
		{
			TWeakObjectPtr<UMJPauseMenuWidget> WeakThis = this;
			CastedWidget->PopUpWithCallback(FOnUserConfirmed::CreateLambda([WeakThis]
			{
				if (WeakThis.IsValid())
				{
					UKismetSystemLibrary::QuitGame(WeakThis->GetWorld(),nullptr,EQuitPreference::Quit,false);
				}
			}), FText::FromString(TEXT("All unsaved changes will be lost. Are you sure you want to quit the game?")));
		}
	}
}

UUserWidget* UMJPauseMenuWidget::GetSettingsWidget()
{
	return SettingsWidget;	
}

UUserWidget* UMJPauseMenuWidget::GetForceExitCautionWidget()
{
	return ForceExitCautionWidget;
}

void UMJPauseMenuWidget::SetPlayerController(APlayerController* InputPC)	
{
	if (IsValid(InputPC))
	{
		PC = InputPC;
	}
}
