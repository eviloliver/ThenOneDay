// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJUIToggle.generated.h"

class UBorder;
class UVerticalBox;
class UHorizontalBox;
class UButton;
/**
* Class Description: 위젯 목록
 * Author: 이지수
 * Created Date: 2025.08.11
 * Last Modified By: 
 * Last Modified Date: 
 */
UCLASS()
class PROJECTMJ_API UMJUIToggle : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Toggle;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> InventoryButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StatPanelButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SkillWidgetButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> List;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> Border;

public:
	UFUNCTION()
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnClickedToggle();

	UButton* GetInventoryButton() {return InventoryButton;};
	UButton* GetStatPanelButton() {return StatPanelButton;};
	UButton* GetSkillWidgetButton() {return SkillWidgetButton;};
};
