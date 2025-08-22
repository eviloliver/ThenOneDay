// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJDetectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJDetectionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Detection;
public:
	virtual void NativeConstruct() override;
	void PlayAnim();
};
