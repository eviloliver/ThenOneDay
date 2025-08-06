// ThenOneDayStudio


#include "TG/UI/MJDungeonEndMenuWidget.h"

#include "ProjectMJ.h"
#include "Character/MJPlayerCharacter.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "Components/Button.h"
#include "GameMode/MJGameModeBase.h"
#include "Kismet/GameplayStatics.h"

class UMJPlayerStatComponent;
class AMJPlayerState;

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
			MJGM->TravelToMap(MAP_TOWN);
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
