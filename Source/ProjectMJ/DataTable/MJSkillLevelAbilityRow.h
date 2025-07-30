
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MJSkillLevelAbilityRow.generated.h"

/**
 * Class Description: 스킬 레벨에 따라 다르게 나가는 Ability를 담은 구조체, Row가 스킬의 레벨
 * Author: 신동민
 * Created Date: 2025.07.29
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FMJSkillLevelAbilityRow : public FTableRowBase
{
	GENERATED_BODY()

public:
    // 레벨별 Ability 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayAbility> ActionSkillAbilityClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayAbility> SkillAbilityClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayAbility> PassiveSkillAbilityClass;

};