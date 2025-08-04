// ThenOneDayStudio


#include "Character/MJForestCreatureCharacter.h"
#include "MJForestCreatureCharacter.h"

AMJForestCreatureCharacter::AMJForestCreatureCharacter()
{

}

void AMJForestCreatureCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}
