// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MJAbilityContextComponent.generated.h"

/**
 * Class Description: 어빌리이 발동에 필요한 데이터를 캐싱(이라 하고 계속 가지고 있는)하는 컴포넌트 
 * Author: 신동민
 * Created Date: 2025.08.01
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

UCLASS( ClassGroup=(AbilityContext), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJAbilityContextComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMJAbilityContextComponent();

protected:

private:

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilityContext")
	FVector LastTargetedMouseLocation;

};
