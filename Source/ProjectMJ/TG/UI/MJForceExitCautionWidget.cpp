// ThenOneDayStudio


#include "TG/UI/MJForceExitCautionWidget.h"

#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMJForceExitCautionWidget::PopUpWithCallback(const FOnUserConfirmed InCallBackFunc)
{
	SetVisibility(ESlateVisibility::Visible);
	CallBackFunc = InCallBackFunc;

	UGameplayStatics::SpawnSound2D(GetWorld(),CautionSound);
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
	UAudioComponent* AudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), SuccessSound);
	if (AudioComp)
	{
		AudioComp->OnAudioFinished.AddDynamic(this, &UMJForceExitCautionWidget::ConfirmInternal);
	}
}

void UMJForceExitCautionWidget::ConfirmInternal()
{
	if (CallBackFunc.IsBound())
	{
		CallBackFunc.Execute();
	}
}
