// Fill out your copyright notice in the Description page of Project Settings.


#include "DM/MJNonPlayerBase.h"

#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

AMJNonPlayerBase::AMJNonPlayerBase()
{
	ASC = CreateDefaultSubobject<UMJAbilitySystemComponent>(TEXT("Ability System Component"));
	AttributeSet = CreateDefaultSubobject<UMJCharacterAttributeSet>(TEXT("Character AttributeSet"));
	SkillAttributeSet = CreateDefaultSubobject<UMJCharacterSkillAttributeSet>(TEXT("Skill AttributeSet"));
}

void AMJNonPlayerBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!ASC)
	{
		return;
	}

	ASC->InitAbilityActorInfo(this, this);

}
