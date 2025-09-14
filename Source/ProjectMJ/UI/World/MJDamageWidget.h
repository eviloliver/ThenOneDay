// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJDamageWidget.generated.h"

enum class EOwnerType : uint8;
struct FGameplayModifierEvaluatedData;
class UMJCharacterAttributeSet;
class UMJAbilitySystemComponent;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJDamageWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Damage;

	UPROPERTY(meta = (BindWidgetAnim),Transient)
	TObjectPtr<UWidgetAnimation> DamageAnim;

	UFUNCTION()
	void OnAnimFinished();
public:
	virtual void NativeConstruct() override;
	void SetDamage(float damage, bool IsCritical, EOwnerType type);
	void SetDamageColor(bool IsCritical, EOwnerType type);
	void PlayAnim();

	FWidgetAnimationDynamicEvent AnimFinishedDelegate;

};
