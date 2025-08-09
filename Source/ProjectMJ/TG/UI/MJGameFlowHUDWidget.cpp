// ThenOneDayStudio


#include "TG/UI/MJGameFlowHUDWidget.h"

#include "MJBossHpBarWidget.h"
#include "MJDungeonEndMenuWidget.h"
#include "MJGameFlowPopUpMsgWidget.h"
#include "MJLoadGameWidget.h"
#include "MJPauseMenuWidget.h"
#include "MJSettingsWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "TG/GameState/MJGameStateDungeon.h"


void UMJGameFlowHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	SaveGameMenu->SetVisibility(ESlateVisibility::Hidden);
	DungeonEndMenu->SetVisibility(ESlateVisibility::Hidden);
	BossHpBar->SetVisibility(ESlateVisibility::Hidden);
	MiniMap->SetVisibility(ESlateVisibility::Visible);
	TimeTextBlock->SetVisibility(ESlateVisibility::Hidden);
	TimeBG->SetVisibility(ESlateVisibility::Hidden);

	CurrTime = 0.0f;
	
	FSlateApplication::Get().OnApplicationActivationStateChanged().AddUObject(this, &UMJGameFlowHUDWidget::OnWindowFocusChanged);
	
	
	SettingsButton->OnClicked.AddDynamic(this,&UMJGameFlowHUDWidget::PauseGame);

	AMJGameStateDungeon* MJDungeonState = Cast<AMJGameStateDungeon>(UGameplayStatics::GetGameState(GetWorld()));
	if (MJDungeonState)
	{
		MJDungeonState->OnAIBossSpawned.AddDynamic(this,&UMJGameFlowHUDWidget::OnBossSpawned);
		MJDungeonState->OnAIBossDied.AddDynamic(this, &UMJGameFlowHUDWidget::OnBossDied);
		
		//MiniMap->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().ClearTimer(TimeWidgetTimerHandle);
		
		TWeakObjectPtr<UMJGameFlowHUDWidget> WeakThis = this;
		GetWorld()->GetTimerManager().SetTimer(TimeWidgetTimerHandle,FTimerDelegate::CreateLambda([WeakThis]
		{
			if (WeakThis.IsValid())	
			{
				WeakThis->CurrTime += 1.0f;
				WeakThis->TimeTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%2d:%02d"), FMath::FloorToInt(WeakThis->CurrTime / 60) ,FMath::FloorToInt(WeakThis->CurrTime) % 60)));
			}
			
		}),1.0f,true,0.0f);
		
		TimeTextBlock->SetVisibility(ESlateVisibility::Visible);
		TimeBG->SetVisibility(ESlateVisibility::Visible);
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
			UMJGameFlowPopUpMsgWidget* ForceExitCautionWidget = Cast<UMJGameFlowPopUpMsgWidget>((PauseMenu->GetForceExitCautionWidget()));
			
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