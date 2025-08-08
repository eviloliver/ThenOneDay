// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJAppear.generated.h"

/**
 * Class Description: 등장 어빌리티 실행 - 임시 제작
 * Author: Kim Minjin
 * Created Date: 2025.08.08.
 * Description of Change:
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJAppear : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJAppear();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
