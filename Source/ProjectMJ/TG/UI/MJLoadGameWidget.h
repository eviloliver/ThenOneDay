// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJChildMenuBaseWidget.h"
#include "MJLoadGameWidget.generated.h"

/**
 * Class Description: LoadGame Widget
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-21
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-21
 */

class UImage;
class UScrollBox;
class UMJLoadGameSlotWidget;
class UButton;

UCLASS()
class PROJECTMJ_API UMJLoadGameWidget : public UMJChildMenuBaseWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClicked_Back();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMJLoadGameSlotWidget> LoadGameSlotWidgetClass;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> SavedGameSlotScrollBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> BackGround;
	
	
	
};
