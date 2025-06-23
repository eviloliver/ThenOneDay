// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "../AbilitySystem/MJCharacterAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "TG/Struct/MJPlayerSessionDataStruct.h"
#include "MJPlayerState.generated.h"


/**
 * Class Description: PlayerState 
 * Author: Cha Tae Gwan
 * Created Date: 2025-06-23
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-06-23
 */
UCLASS()
class PROJECTMJ_API AMJPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMJPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UMJCharacterAttributeSet* GetCharacterAttributeSet() const;

	FMJPlayerSessionData& GetPlayerSessionData();

protected:

	virtual void CopyProperties(APlayerState* PlayerState) override;

	
	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<class UMJAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UMJCharacterAttributeSet> CharacterAttributeSet;

	UPROPERTY()
	FMJPlayerSessionData PlayerSessionData;
	
};


