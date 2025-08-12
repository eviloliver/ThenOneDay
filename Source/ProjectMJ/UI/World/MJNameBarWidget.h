// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJNameBarWidget.generated.h"

class UTextBlock;
/**
* Class Description: 네임바 위젯
 * Author: 이지수
 * Created Date: 2025.08.12
 * Last Modified By: 
 * Last Modified Date: 
 */
UCLASS()
class PROJECTMJ_API UMJNameBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText;

public:
	UFUNCTION()
	void SetNameText(FText Name);
};
