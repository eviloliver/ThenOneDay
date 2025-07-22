// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJChildMenuBaseWidget.h"
#include "MJNewGamePopUpWidget.generated.h"

/**
 * Class Description: LoadGamePopUp Widget
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-21
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-21
 */

class UEditableTextBox;
class UButton;

UCLASS()
class PROJECTMJ_API UMJNewGamePopUpWidget : public UMJChildMenuBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClicked_BackButton();
	
	UFUNCTION()
	void OnClicked_ConfirmButton();

	UFUNCTION()
	int8 GetEmptySlotNum();
	
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> InputPlayerNameTextBox;

	
	
};
