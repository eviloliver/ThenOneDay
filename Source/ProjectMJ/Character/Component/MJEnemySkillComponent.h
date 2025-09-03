// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "MJEnemySkillComponent.generated.h"

/**
 * Class Description: 몬스터의 스킬 컴포넌트
 * Author: 신동민
 * Created Date: 2025.07.30
 * Description of Change: Activate를 Normal, Identity로 나눔, 스킬 관련 초기화
 * Modified By: 김민진
 * Modified Date: 2025.08.01.
 */

class UDataTable;

UCLASS()
class PROJECTMJ_API UMJEnemySkillComponent : public UMJSkillComponentBase
{
	GENERATED_BODY()

private:
	FGameplayTag NormalSkillTag;
	FGameplayTag IdentitySkillTag;
	float GiveChance;
	
public:
	UMJEnemySkillComponent();

	//virtual void PostInitProperties() override;
	virtual void InitializeComponent() override;
	
	virtual void BeginPlay() override;

	virtual UDataTable* GetSkillDataTable() const override;

	void ActivateNormalSkill();
	void ActivateIdentitySkill();

	// Minjin TODO: 확률에 따른 기억(스킬) 전달
	FGameplayTag TryGiveMemory() const;
};
