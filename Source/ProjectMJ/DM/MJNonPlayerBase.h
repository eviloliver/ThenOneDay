// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MJCharacterBase.h"
#include "MJNonPlayerBase.generated.h"

/**
 * Class Description: Test NPC
 * Author: 신동민
 * Created Date: 2025.07.07
 * Last Modified By:
 * Last Modified Date:
 */

class UMJCharacterSkillAttributeSet;
class UMJCharacterAttributeSet;
class UAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class PROJECTMJ_API AMJNonPlayerBase : public AMJCharacterBase
{
	GENERATED_BODY()

public:
	AMJNonPlayerBase();

	//virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;

protected:


	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<UMJCharacterAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<UMJCharacterSkillAttributeSet> SkillAttributeSet;

	UPROPERTY(EditAnywhere, Category = GAS)
	TSubclassOf<UGameplayEffect> InitStatEffect;

};
