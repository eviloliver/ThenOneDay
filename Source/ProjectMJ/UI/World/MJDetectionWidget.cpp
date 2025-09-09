// ThenOneDayStudio


#include "UI/World/MJDetectionWidget.h"

void UMJDetectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnim();
}

void UMJDetectionWidget::PlayAnim()
{
	if (Detection)
	{
		PlayAnimation(Detection);
	}
	
}
