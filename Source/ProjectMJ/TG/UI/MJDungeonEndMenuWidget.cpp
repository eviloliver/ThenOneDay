// ThenOneDayStudio


#include "TG/UI/MJDungeonEndMenuWidget.h"

#include "MJChildMenuBaseWidget.h"
#include "MJGameFlowPopUpMsgWidget.h"
#include "ProjectMJ.h"
#include "Character/MJPlayerCharacter.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "Components/Button.h"
#include "GameMode/MJGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void UMJDungeonEndMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	

	Button_GotoTown->OnClicked.AddDynamic(this,&UMJDungeonEndMenuWidget::OnClicked_GotoTown);

	Button_TryAgain->OnClicked.AddDynamic(this,&UMJDungeonEndMenuWidget::OnClicked_TryAgain);

	
	UMJPlayerStatComponent* MJPlayerStatComp = (Cast<AMJPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this,0))
		->FindComponentByClass<UMJPlayerStatComponent>());
	if (MJPlayerStatComp)
	{
		MJPlayerStatComp->OnDeath.AddDynamic(this,&::UMJDungeonEndMenuWidget::OnDead);
	}
	
	PopUpWidget = Cast<UMJChildMenuBaseWidget>(CreateWidget(this, PopUpWidgetClass));
	if (PopUpWidget)
	{
		PopUpWidget->SetParentWidget(this);
		PopUpWidget->AddToViewport(2);
		PopUpWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UMJDungeonEndMenuWidget::OnClicked_GotoTown()
{
	if (IsValid(PopUpWidget))
	{
		SetVisibility(ESlateVisibility::Hidden);
		UMJGameFlowPopUpMsgWidget* CastedWidget = Cast<UMJGameFlowPopUpMsgWidget>(PopUpWidget);
		
		if (CastedWidget)
		{
			TWeakObjectPtr<UMJDungeonEndMenuWidget> WeakThis = this;
			CastedWidget->PopUpWithCallback(FOnUserConfirmed::CreateLambda([WeakThis]
			{
				if (WeakThis.IsValid())
				{
					APlayerController* PC = UGameplayStatics::GetPlayerController(WeakThis->GetWorld(),0);
					if (PC)
					{
						WeakThis->RemoveFromParent();
						AMJGameModeBase* MJGM = WeakThis->GetWorld()->GetAuthGameMode<AMJGameModeBase>();
						if (MJGM)
						{
							MJGM->TravelToMap(MAP_TOWN);
						}
					}
				}
			}), FText::FromString(TEXT("Are you sure you want to go to town?")));
		}
		
	}
	
}

void UMJDungeonEndMenuWidget::OnClicked_TryAgain()
{
	if (IsValid(PopUpWidget))
	{
		SetVisibility(ESlateVisibility::Hidden);
		UMJGameFlowPopUpMsgWidget* CastedWidget = Cast<UMJGameFlowPopUpMsgWidget>(PopUpWidget);
		
		if (CastedWidget)
		{
			TWeakObjectPtr<UMJDungeonEndMenuWidget> WeakThis = this;
			CastedWidget->PopUpWithCallback(FOnUserConfirmed::CreateLambda([WeakThis]
			{
				if (WeakThis.IsValid())
				{
					WeakThis->GetWorld()->ServerTravel(UGameplayStatics::GetCurrentLevelName(WeakThis->GetWorld()));
				}
			}), FText::FromString(TEXT("Are you sure you want to try this level again?")));
		}
		
	}
}

void UMJDungeonEndMenuWidget::OnDead(AActor* InEffectCauser)
{
	SetVisibility(ESlateVisibility::Visible);
}
