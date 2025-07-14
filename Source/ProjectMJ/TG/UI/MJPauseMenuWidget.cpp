// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/UI/MJPauseMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMJPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Resume->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_Resume);
	Button_Settings->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_Settings);
	Button_MainMenu->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_MainMenu);
}

void UMJPauseMenuWidget::OnClicked_Resume()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		RemoveFromParent();
		PC->SetPause(false);
	}
}

void UMJPauseMenuWidget::OnClicked_Settings()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		RemoveFromParent();

		UUserWidget* SettingsWidget = CreateWidget(PC,SettingsWidgetClass);
		if (SettingsWidget)
		{
			SettingsWidget->AddToViewport(1);
		}
	}
}

void UMJPauseMenuWidget::OnClicked_MainMenu()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		RemoveFromParent();

		UUserWidget* MainMenuWidget = CreateWidget(PC,MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}
