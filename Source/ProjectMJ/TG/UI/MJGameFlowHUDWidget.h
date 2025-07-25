// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJGameFlowHUDWidget.generated.h"

class UMJBossHpBarWidget;
class UMJSettingsWidget;
class UMJDungeonEndMenuWidget;
class UMJForceExitCautionWidget;
class UMJPauseMenuWidget;
/**
 * Class Description: UMJGameFlowHUDWidget Widget
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-24
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-24
 */

UCLASS()
class PROJECTMJ_API UMJGameFlowHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void PauseGame();
	
	void OnWindowFocusChanged(bool bIsFocused);

	void SetPlayerController(APlayerController* InputPC);
	
	UFUNCTION()
	void OnBossSpawned();

	UFUNCTION()
	void OnBossDied();

	UFUNCTION()
	void OnBossHpBarFadeInEnded();	
	
protected:

	
	virtual void NativeConstruct() override;


	TWeakObjectPtr<APlayerController> PC;

	UPROPERTY(meta= (BindWidget))
	TObjectPtr<UMJPauseMenuWidget> PauseMenu;   

	UPROPERTY(meta= (BindWidget))
	TObjectPtr<UMJForceExitCautionWidget> ForceExitCaution;
	
	UPROPERTY(meta= (BindWidget))
	TObjectPtr<UMJDungeonEndMenuWidget> DungeonEndMenu;

	// Boss Section
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMJBossHpBarWidget> BossHpBar;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> BossHpFadeIn;
	
	
};
