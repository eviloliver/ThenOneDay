// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJPlayerStatComponent.h"

#include "ProjectMJ.h"
#include "Character/MJCharacterBase.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Effect/MJGE_SetCharacterAttributeSet.h"

UMJPlayerStatComponent::UMJPlayerStatComponent()
{
	PlayerLevel = 1;
}

void UMJPlayerStatComponent::InitializeStat()
{
	if (!PlayerStatTable)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not exist CurveTable"));
		return;
	}

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not exist OwnerCharacter"));
		return;
	}

	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
	if (!ASC)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not exist ASC"));
		return;
	}

	TSubclassOf<UGameplayEffect> EffectClass = UMJGE_SetCharacterAttributeSet::StaticClass();
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.f, EffectContext);
	if (!SpecHandle.IsValid())
	{
		MJ_LOG(LogMJ, Warning, TEXT("AAA"));
		return;
	}

	for (const auto& CurveTableRow : PlayerStatTable->GetRowMap())
	{
		const FName& RowName = CurveTableRow.Key;
		FRealCurve* Curve = PlayerStatTable->FindCurve(RowName, TEXT("FindCurve"));
		if (Curve)
		{
			float Value = Curve->Eval(PlayerLevel);
			FString TagString = FString::Printf(TEXT("Data.Character.%s"), *RowName.ToString());
			SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName(*TagString)), Value);
		}
	}
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
}
