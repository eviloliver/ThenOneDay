// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MJDetectionWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJDetectionWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UMJDetectionWidgetComponent();

	void SetDetectionWidget();
	
};
