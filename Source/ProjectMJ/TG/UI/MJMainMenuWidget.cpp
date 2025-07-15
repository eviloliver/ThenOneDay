// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/UI/MJMainMenuWidget.h"
#include "ProjectMJ.h"
#include "SkeletalRenderPublic.h"
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
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(this,0);
	if (PC)
	{
		FInputModeUIOnly InputModeUI;
		InputModeUI.SetWidgetToFocus(this->TakeWidget());
		InputModeUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
   
		PC->SetInputMode(InputModeUI);
		
		SettingsWidget = CreateWidget(PC,SettingsWidgetClass);
		if (SettingsWidget)
		{
			SettingsWidget->AddToViewport(2);
			SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		
	}
	
}

void UMJMainMenuWidget::OnClicked_NewGame()
{
	RemoveFromParent();

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FInputModeGameAndUI InputModeGameAndUI;
		PC->SetInputMode(InputModeGameAndUI);
	}

	// Move to TG_Town
	// @fixme : maybe there`s other good method
	
	AMJGameModeBase* GM = Cast<AMJGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		UGameplayStatics::OpenLevel(this,TEXT("TG_Town"));
		//GM->TravelToMap(TEXT("TG_Town"));
	}
}

void UMJMainMenuWidget::OnClicked_LoadGame()
{
	MJ_SLOG(3.0f,FColor::Blue,TEXT("Not Implemented Yet...^^"));
}

void UMJMainMenuWidget::OnClicked_Settings()
{
	SettingsWidget->SetVisibility(ESlateVisibility::Visible);
}
void UMJMainMenuWidget::OnClicked_Quit()
{
	UKismetSystemLibrary::QuitGame(this,nullptr,EQuitPreference::Quit,false);
}
