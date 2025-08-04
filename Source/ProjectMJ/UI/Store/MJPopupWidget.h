// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJPopupWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJPopupWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> YesButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NoButton;

public:
	UButton* GetYesButton() {return YesButton;}
	UButton* GetNoButton() {return NoButton;}
};
