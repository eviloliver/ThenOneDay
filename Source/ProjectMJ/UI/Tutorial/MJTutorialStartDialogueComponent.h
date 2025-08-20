// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Dialogue/MJDialogueComponent.h"
#include "MJTutorialStartDialogueComponent.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTutorialStartDialogueEnd);
UCLASS()
class PROJECTMJ_API UMJTutorialStartDialogueComponent : public UMJDialogueComponent
{
	GENERATED_BODY()

public:
	FOnTutorialStartDialogueEnd OnTutorialStartDialogueEnd;
	
	UFUNCTION()
	void ProceedStory();
};
