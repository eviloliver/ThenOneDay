// ThenOneDayStudio


#include "Dialogue/MJDialogueChoiceWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"


void UMJDialogueChoiceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}

void UMJDialogueChoiceWidget::SetTextBlock(const FString& quest, const FString& point, const FString& exit)
{
	Quest->SetText(FText::FromString(quest));
	Point->SetText(FText::FromString(point));
	Exit->SetText(FText::FromString(exit));
}

