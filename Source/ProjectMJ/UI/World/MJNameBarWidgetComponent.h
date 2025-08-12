// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MJNameBarWidgetComponent.generated.h"

/**
* Class Description: 네임바 위젯 컴포넌트
 * Author: 이지수
 * Created Date: 2025.08.12
 * Last Modified By: 
 * Last Modified Date: 
 */
UCLASS()
class PROJECTMJ_API UMJNameBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

	UMJNameBarWidgetComponent();
public:
	void SetNameBarWidget();
};
