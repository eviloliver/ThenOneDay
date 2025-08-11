// ThenOneDayStudio


#include "UI/MJUIToggle.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"

void UMJUIToggle::NativeConstruct()
{
	Super::NativeConstruct();

	Toggle->SetVisibility(ESlateVisibility::Visible);
	Border->SetVisibility(ESlateVisibility::Hidden);
	List->SetVisibility(ESlateVisibility::Hidden);
	Toggle->OnClicked.AddDynamic(this, &ThisClass::UMJUIToggle::OnClickedToggle);
}

void UMJUIToggle::OnClickedToggle()
{
	if (List->GetVisibility() == ESlateVisibility::Visible)
	{
		Border->SetVisibility(ESlateVisibility::Hidden);
		List->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (List->GetVisibility() == ESlateVisibility::Hidden)
	{
		Border->SetVisibility(ESlateVisibility::Visible);
		List->SetVisibility(ESlateVisibility::Visible);
	}
}
