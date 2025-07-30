// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "MJEnemySkillComponent.generated.h"

/**
 * Class Description: 몬스터의 스킬 컴포넌트
 * Author: 신동민
 * Created Date: 2025.07.30
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

class UDataTable;

UCLASS()
class PROJECTMJ_API UMJEnemySkillComponent : public UMJSkillComponentBase
{
	GENERATED_BODY()
public:
	UMJEnemySkillComponent();

	virtual void BeginPlay() override;

	virtual UDataTable* GetSkillDataTable() const override;

};
