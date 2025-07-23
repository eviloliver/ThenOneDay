// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MJInteractComponent.generated.h"
/**
 * Class Description: 상호작용이 필요한 액터에게 심어주는 컴포넌트 예) NPC - Dialogue, Store 등
 * Author: 이지수
 * Created Date: 2025_07-23
 * Last Modified By: Lee JuHyeon
 * Last Modified Date: Add Using Func from BP 
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJInteractComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Component")
	TArray<TObjectPtr<UActorComponent>> Components;

public:
	void ImplementCompFunction(UActorComponent* Comp);
};
