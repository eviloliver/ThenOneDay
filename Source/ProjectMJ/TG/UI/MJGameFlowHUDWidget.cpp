// ThenOneDayStudio


#include "TG/UI/MJGameFlowHUDWidget.h"

#include "MJBossHpBarWidget.h"
#include "MJDungeonEndMenuWidget.h"
#include "MJDungeonMapWidget.h"
#include "MJForceExitCautionWidget.h"
#include "MJPauseMenuWidget.h"
#include "MJSettingsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TG/GameState/MJGameStateDungeon.h"


void UMJGameFlowHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	ForceExitCaution->SetVisibility(ESlateVisibility::Hidden);
	DungeonEndMenu->SetVisibility(ESlateVisibility::Hidden);
	BossHpBar->SetVisibility(ESlateVisibility::Hidden);
	MiniMap->SetVisibility(ESlateVisibility::Hidden);


	FSlateApplication::Get().OnApplicationActivationStateChanged().AddUObject(this, &UMJGameFlowHUDWidget::OnWindowFocusChanged);

	AMJGameStateDungeon* MJDungeonState = Cast<AMJGameStateDungeon>(UGameplayStatics::GetGameState(GetWorld()));
	if (MJDungeonState)
	{
		MJDungeonState->OnAIBossSpawned.AddDynamic(this,&UMJGameFlowHUDWidget::OnBossSpawned);
		MJDungeonState->OnAIBossDied.AddDynamic(this, &UMJGameFlowHUDWidget::OnBossDied);

		MiniMap->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMJGameFlowHUDWidget::OnBossSpawned()
{
	BossHpBar->SetVisibility(ESlateVisibility::Visible);
	if (!BossHpFadeIn)
	{
		return;
	}
	PlayAnimation(BossHpFadeIn);
}

void UMJGameFlowHUDWidget::OnBossDied()
{
	FWidgetAnimationDynamicEvent AnimEndDelgate;
	AnimEndDelgate.BindDynamic(this,&UMJGameFlowHUDWidget::OnBossHpBarFadeInEnded);
	
	PlayAnimation(BossHpFadeIn,0.0f,1,EUMGSequencePlayMode::Type::Reverse);
	BindToAnimationFinished(BossHpFadeIn,AnimEndDelgate);
}

void UMJGameFlowHUDWidget::OnBossHpBarFadeInEnded()
{
	BossHpBar->SetVisibility(ESlateVisibility::Hidden);
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