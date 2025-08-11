// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJDungeonEndMenuWidget.generated.h"

/**
 * Class Description: DungeonEndMenu Widget
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-22
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-22
 */

class UMJChildMenuBaseWidget;
class UMJGameFlowPopUpMsgWidget;
class UButton;
UCLASS()
class PROJECTMJ_API UMJDungeonEndMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMJGameFlowPopUpMsgWidget> PopUpWidgetClass;

	UPROPERTY()
	TObjectPtr<UMJChildMenuBaseWidget> PopUpWidget;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_GotoTown;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_TryAgain;
	
	UFUNCTION()
	void OnClicked_GotoTown();

	UFUNCTION()
	void OnClicked_TryAgain();

	UFUNCTION()
	void OnDead(AActor* InEffectCauser);
	
};
