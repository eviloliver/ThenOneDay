// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MJCharacterBase.h"
#include "MJ/Interface/MJCharacterAIInterface.h"
#include "Character/Component/MJPlayerSkillComponent.h"
#include "MJMonsterCharacter.generated.h"

class UWidgetComponent;
class UMJEnemyHPBar;
class UMJUIManagerSubsystem;
class UMJCharacterAttributeSet;
class UMJCharacterSkillAttributeSet;
/**
 * Class Description: AICharacter
 * Author: Kim Minjin
 * Created Date: 2025.06.21.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API AMJMonsterCharacter : public AMJCharacterBase, public IMJCharacterAIInterface
{
	GENERATED_BODY()

public:
	AMJMonsterCharacter();

	FGameplayTag GetAttackTag() {return AttackTag;}
	UMJSkillComponentBase* GetSkillComponent() {return SkillComponent;}
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void BeginPlay() override;
	
	// Minjin: Interface
	virtual float GetAIPatrolRadius() override;
	virtual float GetAITurnSpeed() override;
	virtual float GetAIMaximumAttackRange() override;
	virtual float GetAIMinimumAttackRange() override;

	virtual void AttackByAI() override;
	virtual void MeleeAttackByAI() override;
	virtual void RangeAttackByAI() override;
	
	virtual void PossessedBy(AController* NewController) override;

protected:
	UFUNCTION()
	virtual void OnDeath();

	UFUNCTION()
	void OnDamage();

protected:
	// Jisoo : UI Section
	UPROPERTY()
	TObjectPtr<UMJUIManagerSubsystem> UIManager;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> HPBarComponent;


protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMJCharacterAttributeSet> CharacterAttributeSet;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMJCharacterSkillAttributeSet> CharacterSkillAttributeSet;

	// TODO: 우선 base
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gas")
	TObjectPtr<UMJSkillComponentBase> SkillComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;

	// Minjin: Ability Tag
	FGameplayTag AttackTag;
};
