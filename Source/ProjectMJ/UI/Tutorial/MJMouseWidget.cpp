// ThenOneDayStudio


#include "UI/Tutorial/MJMouseWidget.h"

void UMJMouseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnim();
}

void UMJMouseWidget::PlayAnim()
{
	if (MouseLeft)
	{
		PlayAnimation(MouseLeft,0.0f, 0);
	}
}
