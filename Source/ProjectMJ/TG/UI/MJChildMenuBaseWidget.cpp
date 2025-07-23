// ThenOneDayStudio


#include "TG/UI/MJChildMenuBaseWidget.h"

void UMJChildMenuBaseWidget::SetParentWidget(UUserWidget* NewParentWidget)
{
	ParentWidget = NewParentWidget;
}

UUserWidget* UMJChildMenuBaseWidget::GetParentWidget()
{
	return ParentWidget;
}

void UMJChildMenuBaseWidget::BackToParentWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	ParentWidget->SetVisibility(ESlateVisibility::Visible);
}
