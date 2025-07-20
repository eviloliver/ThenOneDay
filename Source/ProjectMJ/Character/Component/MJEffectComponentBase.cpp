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

	TArray<FGameplayTag> EffectTags = {
	FGameplayTag::RequestGameplayTag(FName("State.Debuff.Poisoned")),
	FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stunned")),
	FGameplayTag::RequestGameplayTag(FName("State.Debuff.Burning")),
	FGameplayTag::RequestGameplayTag(FName("State.Debuff.Frozen"))
	};

	for (const FGameplayTag& Tag : EffectTags)
	{
		ASC->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UMJEffectComponentBase::OnStatusTagChanged);
	}
}


void UMJEffectComponentBase::OnStatusTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
    if (CallbackTag == FGameplayTag::RequestGameplayTag(FName("State.Debuff.Poisoned")))
    {
        if (NewCount > 0)
        {
            ApplyPoisonEffect();
        }
        else
        {
            RemovePoisonEffect();
        }
    }
    else if (CallbackTag == FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stunned")))
    {
        if (NewCount > 0)
        {
            ApplyStunEffect();
        }
        else
        {
            RemoveStunEffect();
        }
    }
    else if (CallbackTag == FGameplayTag::RequestGameplayTag(FName("State.Debuff.Burning")))
    {
        if (NewCount > 0)
        {
            ApplyBurningEffect();
        }
        else
        {
            RemoveBurningEffect();
        }
    }
    else if (CallbackTag == FGameplayTag::RequestGameplayTag(FName("State.Debuff.Frozen")))
    {
        if (NewCount > 0)
        {
            ApplyFrozenEffect();
        }
        else
        {
            RemoveFrozenEffect();
        }
    }
    else
    {
        MJ_LOG(LogMJ, Warning, TEXT("Not Exist CallbackTag"));
    }

}

// 여기 태그 가지고 코드 수 줄일 수 있을거 같은데 - 동민 -

void UMJEffectComponentBase::ApplyPoisonEffect()
{
	if (!PoisonVFX)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist PoisonVFX"));
		return;
	}

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}

	if (ActivePoisonVFX && ActivePoisonVFX->IsActive())
	{
		MJ_LOG(LogMJ, Error, TEXT("Already Active"));
		return;
	}

	ActivePoisonVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(PoisonVFX, OwnerCharacter->GetRootComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}

void UMJEffectComponentBase::RemovePoisonEffect()
{
	if (ActivePoisonVFX && ActivePoisonVFX->IsActive())
	{
		ActivePoisonVFX->Deactivate();
	}
}

void UMJEffectComponentBase::ApplyStunEffect()
{
	if (!StunVFX)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist StunVFX"));
		return;
	}

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}

	if (ActiveStunVFX && ActiveStunVFX->IsActive())
	{
		MJ_LOG(LogMJ, Error, TEXT("Already Active"));
		return;
	}

	ActiveStunVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(StunVFX, OwnerCharacter->GetRootComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);

}

void UMJEffectComponentBase::RemoveStunEffect()
{
	if (ActiveStunVFX && ActiveStunVFX->IsActive())
	{
		ActiveStunVFX->Deactivate();
	}
}

void UMJEffectComponentBase::ApplyBurningEffect()
{
	if (!BurningVFX)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist BurningVFX"));
		return;
	}

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}

	if (ActiveBurningVFX && ActiveBurningVFX->IsActive())
	{
		MJ_LOG(LogMJ, Error, TEXT("Already Active"));
		return;
	}

	ActiveBurningVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(BurningVFX, OwnerCharacter->GetRootComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);

}

void UMJEffectComponentBase::RemoveBurningEffect()
{
	if (ActiveBurningVFX && ActiveBurningVFX->IsActive())
	{
		ActiveBurningVFX->Deactivate();
	}
}

void UMJEffectComponentBase::ApplyFrozenEffect()
{
	if (!FrozenVFX)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist FrozenVFX"));
		return;
	}

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}

	if (ActiveFrozenVFX && ActiveFrozenVFX->IsActive())
	{
		MJ_LOG(LogMJ, Error, TEXT("Already Active"));
		return;
	}

	ActiveFrozenVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(FrozenVFX, OwnerCharacter->GetRootComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);

}

void UMJEffectComponentBase::RemoveFrozenEffect()
{
	if (ActiveFrozenVFX && ActiveFrozenVFX->IsActive())
	{
		ActiveFrozenVFX->Deactivate();
	}
}