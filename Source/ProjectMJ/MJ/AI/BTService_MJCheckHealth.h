// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AbilitySystemComponent.h"
#include "BTService_MJCheckHealth.generated.h"

/**
 * Class Description: ServiceNode-Monster Health Check For Monster_Phase 
 * Author: Lee Ju Hyeon
 * Created Date: 2025.08.04.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
class AMJForestCreatureCharacter;
class UAbilitySystemComponent;
class UBlackboardComponent; 

UCLASS()
class PROJECTMJ_API UBTService_MJCheckHealth : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_MJCheckHealth();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	AMJForestCreatureCharacter* ControlledPawn = nullptr;
	UAbilitySystemComponent* CachedASC;
	UBlackboardComponent* Blackboard;
public:

	void EnemyOnChangedHealth(const FOnAttributeChangeData& Data);
};
