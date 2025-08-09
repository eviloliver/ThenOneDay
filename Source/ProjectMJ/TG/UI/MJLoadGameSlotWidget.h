// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJLoadGameSlotWidget.generated.h"

/**
 * Class Description: LoadGameSlot Widget
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-21
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-21
 */

class UHorizontalBox;
class UVerticalBox;
class UTextBlock;
class UBorder;
class USoundCue;
class UMJGameFlowPopUpMsgWidget;

UCLASS()
class PROJECTMJ_API UMJLoadGameSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void SetText(const FText NewSlotNumberText, const FText NewPlayerNameText, const FText NewCreatedDateText,const FText NewRecentPlayedDateText);

	UFUNCTION()
	void SetSlotNum(int8 InputSlotNum);

	UFUNCTION()
	int8 GetSlotNum();
	
protected:

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	void SwitchToInGame();

	UPROPERTY()
	int8 SlotNum;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SlotNumberText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CreatedDateText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RecentPlayedDateText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameText;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> SuccessSound;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> FailSound;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMJGameFlowPopUpMsgWidget> PopUpMessageWidgetClass;

	UPROPERTY()
	TObjectPtr<UMJGameFlowPopUpMsgWidget> PopUpMsgWidget;
	
};
