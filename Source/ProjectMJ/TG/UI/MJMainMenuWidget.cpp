// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/UI/MJMainMenuWidget.h"
#include "ProjectMJ.h"
#include "Components/Button.h"
#include "GameMode/MJGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UMJMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_NewGame->OnClicked.AddDynamic(this, &ThisClass::OnClicked_NewGame);
	Button_LoadGame->OnClicked.AddDynamic(this, &ThisClass::OnClicked_LoadGame);
	Button_Settings->OnClicked.AddDynamic(this, &ThisClass::OnClicked_Settings);
	Button_Quit->OnClicked.AddDynamic(this, &ThisClass::OnClicked_Quit);
}

void UMJMainMenuWidget::OnClicked_NewGame()
{
	RemoveFromParent();
	// Move to TG_Town
	// @fixme : maybe there`s other good method
	AMJGameModeBase* GM = Cast<AMJGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (GM)
	{
		GM->TravelToMap(TEXT("TG_Town"));
	}
}

void UMJMainMenuWidget::OnClicked_LoadGame()
{
	MJ_SLOG(3.0f,FColor::Blue,TEXT("Not Implemented Yet...^^"));
}

void UMJMainMenuWidget::OnClicked_Settings()
{
	RemoveFromParent();
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		UUserWidget* SettingsWidget = CreateWidget(PC,SettingsWidgetClass,TEXT("SettingsWidget"));
		if (SettingsWidget)
		{
			SettingsWidget->AddToViewport();
		}
	}
}
void UMJMainMenuWidget::OnClicked_Quit()
{
	UKismetSystemLibrary::QuitGame(this,nullptr,EQuitPreference::Quit,false);
}
