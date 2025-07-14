// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/UI/MJSettingsWidget.h"

#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

void UMJSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ComboBox_WindowMode->OnSelectionChanged.AddDynamic(this, &UMJSettingsWidget::ComboBox_WindowModeChanged);
	ComboBox_Resolution->OnSelectionChanged.AddDynamic(this, &UMJSettingsWidget::ComboBox_ResolutionChanged);
	ComboBox_Graphics->OnSelectionChanged.AddDynamic(this, &UMJSettingsWidget::ComboBox_GraphicsChanged);
	Button_Back->OnClicked.AddDynamic(this, &UMJSettingsWidget::OnClicked_Back);

}

void UMJSettingsWidget::ComboBox_WindowModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::Type::OnMouseClick)
	{
		UGameUserSettings* CurrentGameUserSettings = GEngine->GetGameUserSettings();
		if (CurrentGameUserSettings)
		{
			if (SelectedItem == "Windowed")
			{
				CurrentGameUserSettings->SetFullscreenMode(EWindowMode::Type::Windowed);
				// Have to change Resolution cuz it might not show it`s windowed UI when changed at same as screen resolution.
				CurrentGameUserSettings->SetScreenResolution(FIntPoint(1280,720));
			}
			else if (SelectedItem == "FullScreen")
			{
				CurrentGameUserSettings->SetFullscreenMode(EWindowMode::Type::Fullscreen);
				CurrentGameUserSettings->SetScreenResolution(FIntPoint(1920,1080));
			}
			else if (SelectedItem == "WindowedFullScreen")
			{
				CurrentGameUserSettings->SetFullscreenMode(EWindowMode::Type::WindowedFullscreen);
			}

			CurrentGameUserSettings->ApplySettings(false);
			CurrentGameUserSettings->SaveSettings();
		}
	}
}

void UMJSettingsWidget::ComboBox_ResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::Type::OnMouseClick)
	{
		UGameUserSettings* CurrentGameUserSettings = GEngine->GetGameUserSettings();
		if (CurrentGameUserSettings)
		{
			if (SelectedItem == "1280 X 720")
			{
				CurrentGameUserSettings->SetScreenResolution(FIntPoint(1280,720));
			}
			else if (SelectedItem == "1600 X 900")
			{
				CurrentGameUserSettings->SetScreenResolution(FIntPoint(1600,900));
			}
			else if (SelectedItem == "1920 X 1080")
			{
				CurrentGameUserSettings->SetScreenResolution(FIntPoint(1920,1080));
			}
			
			CurrentGameUserSettings->ApplySettings(false);
			CurrentGameUserSettings->SaveSettings();
		}
	}
}

void UMJSettingsWidget::ComboBox_GraphicsChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::Type::OnMouseClick)
	{
		UGameUserSettings* CurrentGameUserSettings = GEngine->GetGameUserSettings();
		if (CurrentGameUserSettings)
		{
			// Sets all other settings based on an overall value
			// @param Value 0:low, 1:medium, 2:high, 3:epic, 4:cinematic (gets clamped if needed)
			if (SelectedItem == "Low")
			{
				CurrentGameUserSettings->SetOverallScalabilityLevel(0);
			}
			else if (SelectedItem == "Medium")
			{
				CurrentGameUserSettings->SetOverallScalabilityLevel(1);
			}
			else if (SelectedItem == "High")
			{
				CurrentGameUserSettings->SetOverallScalabilityLevel(2);
			}
			else if (SelectedItem == "Epic")
			{
				CurrentGameUserSettings->SetOverallScalabilityLevel(3);
			}
			else if (SelectedItem == "Cinematic")
			{
				CurrentGameUserSettings->SetOverallScalabilityLevel(4);
			}
			
			CurrentGameUserSettings->ApplySettings(false);
			CurrentGameUserSettings->SaveSettings();
		}
	}
}

void UMJSettingsWidget::OnClicked_Back()
{
	RemoveFromParent();
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		if (PC->IsPaused())
		{
			
			UUserWidget* PauseWidget = CreateWidget(PC, PauseMenuWidgetClass);
			if (PauseWidget)
			{
				PauseWidget->AddToViewport();
			}
		}
		else
		{
			UUserWidget* MainMewnuWidget = CreateWidget(PC, MainMenuWidgetClass);
			if (MainMewnuWidget)
			{
				MainMewnuWidget->AddToViewport();
			}		
		}
	}
}
