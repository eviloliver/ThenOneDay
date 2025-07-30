// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJPlayerStatComponent.h"

#include "ProjectMJ.h"
#include "Character/MJCharacterBase.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Effect/MJGE_SetCharacterAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

UMJPlayerStatComponent::UMJPlayerStatComponent()
{
	PlayerLevel = 1;
	
}

void UMJPlayerStatComponent::InitializeStat()
{
	// 다음 필요 경험치 계산
	bIsInitializingStats = true;

	ExperienceForNextLevel = GetTotalExperienceForLevel(PlayerLevel + 1);

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
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = ASC->GetSet<UMJCharacterAttributeSet>()->GetMaxMovementSpeed();

	bIsInitializingStats = false;
}

void UMJPlayerStatComponent::GainExperience(int32 GainedExp)
{
	if (GainedExp <= 0)
	{
		MJ_LOG(LogMJ, Warning, TEXT("GainedExp is zero under"))
		return;
	}

	TotalCumulativeExperience += GainedExp;
	CheckForLevelUp();
	OnExperienceChanged.Broadcast(GetNumerator() ,GetDenominator());
}

void UMJPlayerStatComponent::CheckForLevelUp()
{
	if (ExperienceForNextLevel <= 0)
	{
		MJ_LOG(LogMJ, Warning, TEXT("ExperienceForNextLevel is zero under"))
		return;
	}

	while(TotalCumulativeExperience >= ExperienceForNextLevel)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Level Up"))
		++PlayerLevel;

		InitializeStat();

		OnLevelUp.Broadcast(PlayerLevel);
		
	}

}

float UMJPlayerStatComponent::GetTotalExperienceForLevel(int32 Level) const
{
	// 데미지 공식 부분
	// 현재는 n^3
	float TotalExp = FMath::Pow(Level, 3.0f);

	return TotalExp;
}

float UMJPlayerStatComponent::GetNumerator()
{
	
	if (PlayerLevel == 1)
	{
		Numerator = TotalCumulativeExperience;
	}
	else
	{
		Numerator = TotalCumulativeExperience - GetTotalExperienceForLevel(PlayerLevel);
	}

	return Numerator;
}

float UMJPlayerStatComponent::GetDenominator()
{
	Denominator = ExperienceForNextLevel - GetTotalExperienceForLevel(PlayerLevel);
	if (PlayerLevel == 1)
	{
		Denominator = GetTotalExperienceForLevel(PlayerLevel + 1);
	}
	else
	{
		Denominator = ExperienceForNextLevel - GetTotalExperienceForLevel(PlayerLevel);
	}
	return	Denominator;
}
