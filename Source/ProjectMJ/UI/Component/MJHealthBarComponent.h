// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MJHealthBarComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
	UMJHealthBarComponent();

public:
	void SetHPBarWidget();
};
