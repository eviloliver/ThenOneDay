// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJSkillAttack.generated.h"

/**
 * Class Description: IdentitySkill을 이용한 공격
 * Author: Kim Minjin
 * Created Date: 2025.08.01..
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJSkillAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJSkillAttack();

protected:
	FDelegateHandle Handle;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
};
