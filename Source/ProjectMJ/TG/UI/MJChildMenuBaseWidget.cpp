// ThenOneDayStudio


#include "TG/UI/MJChildMenuBaseWidget.h"

void UMJChildMenuBaseWidget::SetParentWidget(UUserWidget* NewParentWidget)
{
	if (IsValid(NewParentWidget))
	{
		ParentWidget = NewParentWidget;
	}
}

UUserWidget* UMJChildMenuBaseWidget::GetParentWidget()
{
	return ParentWidget.Get();
}

void UMJChildMenuBaseWidget::BackToParentWidget()
{
	if (ParentWidget.IsValid())
	{
		SetVisibility(ESlateVisibility::Hidden);
		ParentWidget->SetVisibility(ESlateVisibility::Visible);	
	}
}
