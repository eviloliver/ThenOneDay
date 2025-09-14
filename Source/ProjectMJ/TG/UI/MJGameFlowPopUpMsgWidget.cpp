// ThenOneDayStudio


#include "TG/UI/MJGameFlowPopUpMsgWidget.h"

#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void UMJGameFlowPopUpMsgWidget::PopUpWithCallback(const FOnUserConfirmed InCallBackFunc, const FText InText)
{
	SetVisibility(ESlateVisibility::Visible);
	CallBackFunc = InCallBackFunc;
	PopUptext->SetText(InText);
	UGameplayStatics::SpawnSound2D(GetWorld(),CautionSound);
}

void UMJGameFlowPopUpMsgWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackButton->OnClicked.AddDynamic(this, &UMJGameFlowPopUpMsgWidget::OnClicked_BackButton);
	ConfirmButton->OnClicked.AddDynamic(this, &UMJGameFlowPopUpMsgWidget::OnClicked_ConfirmButton);
}

void UMJGameFlowPopUpMsgWidget::OnClicked_BackButton()
{
	BackToParentWidget();
}

void UMJGameFlowPopUpMsgWidget::OnClicked_ConfirmButton()
{
	ConfirmInternal();
}

void UMJGameFlowPopUpMsgWidget::ConfirmInternal()
{
	if (CallBackFunc.IsBound())
	{
		CallBackFunc.Execute();
		SetVisibility(ESlateVisibility::Hidden);
	}
}
