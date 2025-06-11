// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "ProjectMJPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API AProjectMJPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AProjectMJPlayerState();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UProjectMJCharacterAttributeSet> CharacterAttributeSet;
	
};

