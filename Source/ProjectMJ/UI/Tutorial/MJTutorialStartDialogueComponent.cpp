// ThenOneDayStudio


#include "UI/Tutorial/MJTutorialStartDialogueComponent.h"

void UMJTutorialStartDialogueComponent::ProceedStory()
{
	TurnOver();
	if (IsDialogueEnd())
	{
		OnTutorialStartDialogueEnd.Broadcast();
	}
	
}
