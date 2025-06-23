// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MJCharacterBase.generated.h"

class UMJAbilitySystemComponent;
class UMJAttributeSet;
class UDataAsset_StartDataBase;
/**
 * Class Description: CharacterBase
 * Author: Lee JuHyeon
 * Created Date: 2025_06_11
 * Last Modified By: Lee JuHyeon
 * Last Modified Date: Add DA_StartData
 */
UCLASS()
class PROJECTMJ_API AMJCharacterBase : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMJCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	
	virtual void PossessedBy(AController* NewController)override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UMJAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSoftObjectPtr<UDataAsset_StartDataBase>CharacterStartData;
};


