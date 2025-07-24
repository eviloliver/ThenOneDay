// ThenOneDayStudio


#include "TG/UI/MJForceExitCautionWidget.h"

#include "Components/Button.h"

void UMJForceExitCautionWidget::PopUpWithCallback(const FOnUserConfirmed InCallBackFunc)
{
	SetVisibility(ESlateVisibility::Visible);
	CallBackFunc = InCallBackFunc;
}

void UMJForceExitCautionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackButton->OnClicked.AddDynamic(this, &UMJForceExitCautionWidget::OnClicked_BackButton);
	ConfirmButton->OnClicked.AddDynamic(this, &UMJForceExitCautionWidget::OnClicked_ConfirmButton);
}

void UMJForceExitCautionWidget::OnClicked_BackButton()
{
	BackToParentWidget();
}

void UMJForceExitCautionWidget::OnClicked_ConfirmButton()
{
	if (CallBackFunc.IsBound())
	{
		CallBackFunc.Execute();
	}
}
