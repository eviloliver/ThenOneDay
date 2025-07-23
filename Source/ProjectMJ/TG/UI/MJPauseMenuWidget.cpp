// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/UI/MJPauseMenuWidget.h"

#include "MJSettingsWidget.h"
#include "Components/Button.h"
#include "Components/Spacer.h"
#include "Controller/MJPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MJPlayerState.h"
#include "TG/GameMode/MJGameModeDungeonTG.h"
#include "TG/GameMode/MJGameModeTownTG.h"
#include "TG/SubSystem/MJSaveGameSubsystem.h"

void UMJPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Resume->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_Resume);
	Button_Settings->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_Settings);
	Button_MainMenu->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_MainMenu);
	Button_SaveGame->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_SaveGame);
	Button_GotoTown->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_GotoTown);
	Button_QuitGame->OnClicked.AddDynamic(this, &UMJPauseMenuWidget::OnClicked_QuitGame);

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		SettingsWidget = Cast<UMJChildMenuBaseWidget>(CreateWidget(PC, SettingsWidgetClass));
		if (SettingsWidget)
		{		
			SettingsWidget->SetParentWidget(this);
			SettingsWidget->AddToViewport(2);
			SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
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
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		AMJPlayerController* MJPC = Cast<AMJPlayerController>(PC);
		if (MJPC)
		{
			UUserWidget* PauseWidget = MJPC->GetPauseWidget();
			if (PauseWidget)
			{
				PauseWidget->SetVisibility(ESlateVisibility::Hidden);
				
				if (PC->IsPaused())
				{
					PC->SetPause(false);
				}		
			}
		}
	}
}

void UMJPauseMenuWidget::OnClicked_SaveGame()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
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
	UMJSettingsWidget* MJSettingsWidget = Cast<UMJSettingsWidget>(SettingsWidget);
	if (MJSettingsWidget)
	{
		SetVisibility(ESlateVisibility::Hidden);
		MJSettingsWidget->SetParentWidget(this);
		MJSettingsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMJPauseMenuWidget::OnClicked_MainMenu()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		RemoveFromParent();
		UGameplayStatics::OpenLevel(GetWorld(),TEXT("TG_MainMenu"));
	}
}

void UMJPauseMenuWidget::OnClicked_GotoTown()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		RemoveFromParent();
		AMJGameModeBase* MJGM = GetWorld()->GetAuthGameMode<AMJGameModeBase>();
		if (MJGM)
		{
			MJGM->TravelToMap(TEXT("TG_Town"));
		}
	}
}

void UMJPauseMenuWidget::OnClicked_QuitGame()
{
	UKismetSystemLibrary::QuitGame(this,nullptr,EQuitPreference::Quit,false);
}


UUserWidget* UMJPauseMenuWidget::GetSettingsWidget()
{
	return SettingsWidget;	
}
