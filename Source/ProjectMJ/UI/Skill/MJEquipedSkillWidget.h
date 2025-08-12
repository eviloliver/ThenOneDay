// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJEquipedSkillWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJEquipedSkillWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> InstantImage;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> ChargingImage;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> PassiveImage;

public:
	void SetInstantImage(UTexture2D* ItemTexture);
	void SetChargingImage(UTexture2D* ItemTexture);
	void SetPassiveImage(UTexture2D* ItemTexture);
};
