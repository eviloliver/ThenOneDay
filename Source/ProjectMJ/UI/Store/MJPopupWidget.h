// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJPopupWidget.generated.h"

class UTextBlock;
class UButton;

/**
* Class Description: 구매 혹은 판매 버튼을 누르면 나오는 위젯
 * Author: 이지수
 * Created Date: 2025.08.09
 * Last Modified By: 
 * Last Modified Date: 
 */

UCLASS()
class PROJECTMJ_API UMJPopupWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Notification;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> YesButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NoButton;

public:
	void SetNotification(FText notification);
	UButton* GetYesButton() {return YesButton;}
	UButton* GetNoButton() {return NoButton;}
};
