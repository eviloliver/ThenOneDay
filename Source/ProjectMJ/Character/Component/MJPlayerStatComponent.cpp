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
