// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJChildMenuBaseWidget.h"
#include "MJGameFlowPopUpMsgWidget.generated.h"

/**
 * Class Description: UMJGameFlowPopUpMsgWidget Widget
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-24
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-24
 */

class UTextBlock;
DECLARE_DELEGATE(FOnUserConfirmed)

class UButton;
class USoundCue;
UCLASS()
class PROJECTMJ_API UMJGameFlowPopUpMsgWidget : public UMJChildMenuBaseWidget
{
	GENERATED_BODY()

public:

	void PopUpWithCallback(const FOnUserConfirmed InCallBackFunc, const FText InText);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClicked_BackButton();
	
	UFUNCTION()
	void OnClicked_ConfirmButton();

	UFUNCTION()
	void ConfirmInternal();

	FOnUserConfirmed CallBackFunc;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PopUptext;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> SuccessSound;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> CautionSound;

	
};
