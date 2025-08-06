// ThenOneDayStudio


#include "TG/Actor/MJPortalToTown.h"

#include "ProjectMJ.h"
#include "GameMode/MJGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AMJPortalToTown::AMJPortalToTown()
{
}

void AMJPortalToTown::Execute()
{
	Super::Execute();
	AGameModeBase* GM = UGameplayStatics::GetGameMode(GetWorld());
	if (IsValid(GM))
	{
		AMJGameModeBase* MJGM = Cast<AMJGameModeBase>(GM);
		if (IsValid(MJGM))
		{
			MJGM->TravelToMap(MAP_TOWN);	
		}
	}
}
