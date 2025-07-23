// ThenOneDayStudio


#include "UI/Component/MJInteractComponent.h"
#include "Dialogue/MJDialogueComponent.h"

// Sets default values for this component's properties

void UMJInteractComponent::ImplementCompFunction(UActorComponent* Comp)
{
	if (UMJDialogueComponent* DialogueComp = Cast<UMJDialogueComponent>(Comp))
	{
		
	}
}
