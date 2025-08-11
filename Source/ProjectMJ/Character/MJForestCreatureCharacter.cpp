// ThenOneDayStudio


#include "Character/MJForestCreatureCharacter.h"
#include "MJForestCreatureCharacter.h"
#include "ProjectMJ.h"
#include "Character/Component/MJEnemySkillComponent.h"
#include "DataTable/MJSkillDataRow.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

AMJForestCreatureCharacter::AMJForestCreatureCharacter()
{

}

void AMJForestCreatureCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	
	
}
