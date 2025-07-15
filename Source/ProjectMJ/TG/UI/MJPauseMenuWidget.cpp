// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/UI/MJPauseMenuWidget.h"

#include "Components/Button.h"
#include "Controller/MJPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UMJPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Resume->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_Resume);
	Button_Settings->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_Settings);
	Button_MainMenu->OnClicked.AddDynamic(this,&UMJPauseMenuWidget::OnClicked_MainMenu);

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		SettingsWidget = CreateWidget(PC, SettingsWidgetClass);
		if (SettingsWidget)
		{
			SettingsWidget->AddToViewport(2);
			SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
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

void UMJPauseMenuWidget::OnClicked_Settings()
{
	SettingsWidget->SetVisibility(ESlateVisibility::Visible);
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

UUserWidget* UMJPauseMenuWidget::GetSettingsWidget()
{
	return SettingsWidget;	
}
