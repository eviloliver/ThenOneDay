// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJHUDWidget.generated.h"

/**
 * Class Description: HUD
 * Author: 이지수
 * Created Date: 2025.06.26
 * Last Modified By: 
 * Last Modified Date: 
 */

class UMJHealthBarWidget;
class UMJManaBarWidget;
class UMJExperienceWidget;
class UMJStatWidget;

UCLASS()
class PROJECTMJ_API UMJHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UMJHealthBarWidget* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UMJManaBarWidget* ManaBar;

	UPROPERTY(meta = (BindWidget))
	UMJExperienceWidget* ExpBar;

	UPROPERTY(meta = (BindWidget))
	UMJStatWidget* StatPanel;
	
public:
	void BindAtrributesToChildren(class UMJAbilitySystemComponent* ASC, class UMJCharacterAttributeSet* AttributeSet);
};
