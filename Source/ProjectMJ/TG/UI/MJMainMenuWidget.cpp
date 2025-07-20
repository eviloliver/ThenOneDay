// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/UI/MJMainMenuWidget.h"

#include "MJSettingsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UMJMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_NewGame->OnClicked.AddDynamic(this, &ThisClass::OnClicked_NewGame);
	Button_LoadGame->OnClicked.AddDynamic(this, &ThisClass::OnClicked_LoadGame);
	Button_Settings->OnClicked.AddDynamic(this, &ThisClass::OnClicked_Settings);
	Button_Quit->OnClicked.AddDynamic(this, &ThisClass::OnClicked_Quit);
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(this->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
   
		PC->SetInputMode(InputMode);

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
	}
}

void UMJMainMenuWidget::OnClicked_NewGame()
{
	
	
	SetVisibility(ESlateVisibility::Hidden);
	NewGamePopUpWidget->SetVisibility(ESlateVisibility::Visible);
	

	// Move to TG_Town
	// @fixme : maybe there`s other good method
	//UGameplayStatics::OpenLevel(this,TEXT("TG_Town"));
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
	UKismetSystemLibrary::QuitGame(this,nullptr,EQuitPreference::Quit,false);
}
