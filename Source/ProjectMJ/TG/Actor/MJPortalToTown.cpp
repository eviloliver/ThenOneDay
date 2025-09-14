// ThenOneDayStudio


#include "TG/Actor/MJPortalToTown.h"

#include "ProjectMJ.h"
#include "GameMode/MJGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AMJPortalToTown::AMJPortalToTown()
{
	
	// TG : Don`t change this for proper SpawnActor
	SetActorRelativeScale3D(FVector(0.38f,0.2f,0.38f));
}

void AMJPortalToTown::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	// TG : Don`t change this for proper SpawnActor
	SetActorRelativeScale3D(FVector(0.38f,0.2f,0.38f));
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
