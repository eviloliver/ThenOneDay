// ThenOneDayStudio


#include "UI/Store/MJPopupWidget.h"
#include "Components/TextBlock.h"

void UMJPopupWidget::SetNotification(FText notification)
{
	Notification->SetText(notification);
}
