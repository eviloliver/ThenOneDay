// ThenOneDayStudio

#include "TG/Actor/MJSavePointActor.h"

#include "Controller/MJPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TG/UI/MJGameFlowHUDWidget.h"
#include "TG/UI/MJLoadGameWidget.h"

AMJSavePointActor::AMJSavePointActor()
{
}

void AMJSavePointActor::Execute()
{
	Super::Execute();
	
	AMJPlayerController* MJPC = Cast<AMJPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (MJPC)
	{
		MJPC->GetGameFlowHUD()->GetSaveGameWidget()->SetVisibility(ESlateVisibility::Visible);
	}
}

