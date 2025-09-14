// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJGameFlowHUDWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;
class UMJLoadGameWidget;
class UMJDungeonMapWidget;
class UMJBossHpBarWidget;
class UMJSettingsWidget;
class UMJDungeonEndMenuWidget;
class UMJGameFlowPopUpMsgWidget;
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
	
	FORCEINLINE UMJLoadGameWidget* GetSaveGameWidget() {return SaveGameMenu;}
	FORCEINLINE UMJDungeonMapWidget* GetDungeonMapWidget() {return DungeonMap;}
	
protected:

	
	virtual void NativeConstruct() override;

	TWeakObjectPtr<APlayerController> PC;

	UPROPERTY(meta= (BindWidget))
	TObjectPtr<UMJPauseMenuWidget> PauseMenu;

	UPROPERTY(meta= (BindWidget))
	TObjectPtr<UMJLoadGameWidget> SaveGameMenu;
	
	UPROPERTY(meta= (BindWidget))
	TObjectPtr<UMJDungeonEndMenuWidget> DungeonEndMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJDungeonMapWidget> DungeonMap;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> MiniMap;


	// Boss Section
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMJBossHpBarWidget> BossHpBar;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> BossHpFadeIn;

	// Time Section
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> TimeBG;
	
	UPROPERTY()
	float CurrTime;

	UPROPERTY()
	FTimerHandle TimeWidgetTimerHandle;

	// Button Section
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> InventoryButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> StatButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> QuestButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> SettingsButton;

	
};
