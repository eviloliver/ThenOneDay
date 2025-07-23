// ThenOneDayStudio


#include "TG/UI/MJDungeonEndMenuWidget.h"

#include "Components/Button.h"
#include "GameMode/MJGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MJPlayerState.h"

class AMJPlayerState;

void UMJDungeonEndMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	

	Button_GotoTown->OnClicked.AddDynamic(this,&UMJDungeonEndMenuWidget::OnClicked_GotoTown);

	Button_TryAgain->OnClicked.AddDynamic(this,&UMJDungeonEndMenuWidget::OnClicked_TryAgain);

	AMJPlayerState* MJPS = Cast<AMJPlayerState>(UGameplayStatics::GetPlayerState(this,0));
	if (MJPS)
	{
		MJPS->GetCharacterAttributeSet()->OnDeath.AddDynamic(this,&UMJDungeonEndMenuWidget::OnDead);
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UMJDungeonEndMenuWidget::OnClicked_GotoTown()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC)
	{
		RemoveFromParent();
		AMJGameModeBase* MJGM = GetWorld()->GetAuthGameMode<AMJGameModeBase>();
		if (MJGM)
		{
			MJGM->TravelToMap(TEXT("TG_Town"));
		}
	}
}

void UMJDungeonEndMenuWidget::OnClicked_TryAgain()
{
	GetWorld()->ServerTravel(UGameplayStatics::GetCurrentLevelName(GetWorld()));
}

void UMJDungeonEndMenuWidget::OnDead(AActor* InEffectCauser)
{
	SetVisibility(ESlateVisibility::Visible);
	
}
