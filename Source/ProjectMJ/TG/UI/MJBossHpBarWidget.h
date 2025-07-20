
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJBossHpBarWidget.generated.h"

struct FOnAttributeChangeData;
class UProgressBar;
/**
 * Class Description: BossHpBarWidget 
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-19
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-19
 */
UCLASS()
class PROJECTMJ_API UMJBossHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION()
	void BindToAttributes();

protected:
	
	virtual void NativeConstruct() override;

	void OnHealthChanged(const FOnAttributeChangeData& Data);

	void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UProgressBar> HpProgressBar;

	UPROPERTY()
	float CurrentHealth;

	UPROPERTY()
	float CurrentMaxHealth;
	
	
};
