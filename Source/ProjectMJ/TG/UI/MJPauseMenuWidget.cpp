// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/UI/MJPauseMenuWidget.h"

#include "MJForceExitCautionWidget.h"
#include "Components/Button.h"
#include "Components/Spacer.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MJPlayerState.h"
#include "TG/GameMode/MJGameModeDungeonTG.h"
#include "TG/GameMode/MJGameModeTownTG.h"
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
	Button_SaveGame->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_SaveGame);
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

		if (AMJGameModeTownTG* GMTown = GetWorld()->GetAuthGameMode<AMJGameModeTownTG>())
		{
			Spacer_GotoTown->SetVisibility(ESlateVisibility::Collapsed);
			Button_GotoTown->SetVisibility(ESlateVisibility::Collapsed);
		}
		else if (AMJGameModeDungeonTG* GMDungeon = GetWorld()->GetAuthGameMode<AMJGameModeDungeonTG>())
		{
			Spacer_GotoTown->SetVisibility(ESlateVisibility::Visible);
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
		UMJForceExitCautionWidget* CastedWidget = Cast<UMJForceExitCautionWidget>(ForceExitCautionWidget);
		
		if (CastedWidget)
		{
			CastedWidget->PopUpWithCallback(FOnUserConfirmed::CreateLambda([this]
			{
				AMJGameModeBase* MJGM = GetWorld()->GetAuthGameMode<AMJGameModeBase>();
				if (MJGM)
				{
					MJGM->TravelToMap(TEXT("MainMenu"));
				}
			}));
		}
	}
}

void UMJPauseMenuWidget::OnClicked_GotoTown()
{
	if (PC.IsValid())
	{

		SetVisibility(ESlateVisibility::Hidden);
		UMJForceExitCautionWidget* CastedWidget = Cast<UMJForceExitCautionWidget>(ForceExitCautionWidget);
		
		if (CastedWidget)
		{
			CastedWidget->PopUpWithCallback(FOnUserConfirmed::CreateLambda([this]
			{
				AMJGameModeBase* MJGM = GetWorld()->GetAuthGameMode<AMJGameModeBase>();
				if (MJGM)
				{
					MJGM->TravelToMap(TEXT("TG_Town"));
				}
			}));
		}
		
	}
}

void UMJPauseMenuWidget::OnClicked_QuitGame()
{
	if (IsValid(ForceExitCautionWidget))
	{
		SetVisibility(ESlateVisibility::Hidden);
		UMJForceExitCautionWidget* CastedWidget = Cast<UMJForceExitCautionWidget>(ForceExitCautionWidget);
		
		if (CastedWidget)
		{
			CastedWidget->PopUpWithCallback(FOnUserConfirmed::CreateLambda([this]
			{
				UKismetSystemLibrary::QuitGame(GetWorld(),nullptr,EQuitPreference::Quit,false);
			}));
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
