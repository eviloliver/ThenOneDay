// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJChildMenuBaseWidget.h"
#include "MJForceExitCautionWidget.generated.h"

/**
 * Class Description: UMJForceExitCautionWidget Widget
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-24
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-24
 */

DECLARE_DELEGATE(FOnUserConfirmed)

class UButton;
UCLASS()
class PROJECTMJ_API UMJForceExitCautionWidget : public UMJChildMenuBaseWidget
{
	GENERATED_BODY()

public:

	void PopUpWithCallback(const FOnUserConfirmed InCallBackFunc);

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
	TObjectPtr<UButton> BackButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundWave> SuccessSound;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundWave> CautionSound;

	
};
