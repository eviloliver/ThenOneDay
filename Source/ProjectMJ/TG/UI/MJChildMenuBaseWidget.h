// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJChildMenuBaseWidget.generated.h"

/**
 * Class Description: UMJChildMenuBaseWidget Widget (
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-21
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-21
 */
UCLASS()
class PROJECTMJ_API UMJChildMenuBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetParentWidget(UUserWidget* NewParentWidget);

	UFUNCTION()
	UUserWidget* GetParentWidget();
	
	UFUNCTION(BlueprintCallable)
	void BackToParentWidget();

protected:

	
	UPROPERTY()
	TObjectPtr<UUserWidget> ParentWidget;

	
	
};
