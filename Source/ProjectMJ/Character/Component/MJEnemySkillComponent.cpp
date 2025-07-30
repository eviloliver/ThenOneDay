// ThenOneDayStudio


#include "Character/Component/MJEnemySkillComponent.h"

#include "ProjectMJ.h"
#include "DataTable/MJSkillDataRow.h"
#include "TG/MJGameInstanceTG.h"

UMJEnemySkillComponent::UMJEnemySkillComponent()
{

}

void UMJEnemySkillComponent::BeginPlay()
{
	Super::BeginPlay();
}

UDataTable* UMJEnemySkillComponent::GetSkillDataTable() const
{
	UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
	if (!GI)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist GI"));
		return nullptr;
	}
	UDataTable* SkillDataTable = GI->EnemySkillDataTable;
	if (!SkillDataTable)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist SkillDataTable"));
		return nullptr;
	}
	return SkillDataTable;
}
