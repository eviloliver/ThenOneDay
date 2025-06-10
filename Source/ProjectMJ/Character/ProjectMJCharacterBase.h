// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ProjectMJCharacterBase.generated.h"

class UProjectMJAbilitySystemComponent;
class UProjectMJAttributeSet;
UCLASS()
class PROJECTMJ_API AProjectMJCharacterBase : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProjectMJCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	
	virtual void PossessedBy(AController* NewController)override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UProjectMJAbilitySystemComponent> ASC;


};


