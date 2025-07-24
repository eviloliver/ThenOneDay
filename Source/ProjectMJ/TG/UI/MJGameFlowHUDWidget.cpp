// ThenOneDayStudio


#include "TG/UI/MJGameFlowHUDWidget.h"

#include "MJDungeonEndMenuWidget.h"
#include "MJForceExitCautionWidget.h"
#include "MJPauseMenuWidget.h"
#include "MJSettingsWidget.h"


void UMJGameFlowHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	ForceExitCaution->SetVisibility(ESlateVisibility::Hidden);
	DungeonEndMenu->SetVisibility(ESlateVisibility::Hidden);

	FSlateApplication::Get().OnApplicationActivationStateChanged().AddUObject(this, &UMJGameFlowHUDWidget::OnWindowFocusChanged);
	
}

void UMJGameFlowHUDWidget::PauseGame()
{
	if (PC.IsValid())
	{
		if (PC->IsPaused())
		{
			UMJSettingsWidget* SettingsWidget = Cast<UMJSettingsWidget>((Cast<UMJPauseMenuWidget>(PauseMenu)->GetSettingsWidget()));
			UMJForceExitCautionWidget* ForceExitCautionWidget = Cast<UMJForceExitCautionWidget>((PauseMenu->GetForceExitCautionWidget()));
			
			if ( SettingsWidget && ForceExitCautionWidget)
			{
				if (SettingsWidget->GetVisibility() == ESlateVisibility::Visible)
				{
					SettingsWidget->BackToParentWidget();
				}
				else if (ForceExitCautionWidget->GetVisibility() == ESlateVisibility::Visible)
				{
					ForceExitCautionWidget->BackToParentWidget();
				}
				else
				{
					PauseMenu->SetVisibility(ESlateVisibility::Hidden);
					PC->SetPause(false);		
				}
			}
		}
		else
		{
			PauseMenu->SetVisibility(ESlateVisibility::Visible);
			PC->SetPause(true);
		}	
	}
}

void UMJGameFlowHUDWidget::OnWindowFocusChanged(bool bIsFocused)
{
	if (PC.IsValid())
	{
		if (bIsFocused)
        {
        	
        }
        else
        {
        	PauseMenu->SetVisibility(ESlateVisibility::Visible);
        	PC->SetPause(true);
        }
	}
}

void UMJGameFlowHUDWidget::SetPlayerController(APlayerController* InputPC)
{
	if (IsValid(InputPC))
	{
		PC = InputPC;
		PauseMenu->SetPlayerController(InputPC);
	}
}