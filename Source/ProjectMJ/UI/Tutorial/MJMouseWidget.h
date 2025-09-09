// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJMouseWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJMouseWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidgetAnim),Transient)
	TObjectPtr<UWidgetAnimation> MouseLeft;
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void PlayAnim();
};
