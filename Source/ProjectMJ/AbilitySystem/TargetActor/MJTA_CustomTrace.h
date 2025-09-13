// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/MJTA_Trace.h"
#include "MJTA_CustomTrace.generated.h"

/**
 * Class Description: 모양 및 위치를 선택할 수 있는 Trace
 * Author: Kim Minjin
 * Created Date: 2025.08.20.
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

UENUM(BlueprintType)
enum class ETraceShape: uint8
{
	Sphere = 0,
	Capsule = 1,
};

UCLASS()
class PROJECTMJ_API AMJTA_CustomTrace : public AMJTA_Trace
{
	GENERATED_BODY()

public:
	AMJTA_CustomTrace();
	void SetLocation(FVector InLocation){TraceLocation = InLocation;};

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;

	FVector TraceLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ETraceShape TraceShape;
};
