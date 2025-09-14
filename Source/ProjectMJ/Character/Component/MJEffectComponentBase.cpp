// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJEffectComponentBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Character/MJCharacterBase.h"

// TODO: SFX 재생

UMJEffectComponentBase::UMJEffectComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMJEffectComponentBase::BeginPlay()
{
	Super::BeginPlay();

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}

	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
	if (!ASC)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist ASC"));
		return;
	}

}