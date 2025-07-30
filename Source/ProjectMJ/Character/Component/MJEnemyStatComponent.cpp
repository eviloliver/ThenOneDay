// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJEnemyStatComponent.h"

#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Effect/MJGE_SetCharacterAttributeSet.h"
#include "DataTable/MJEnemyDataRow.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "TG/MJGameInstanceTG.h"


UMJEnemyStatComponent::UMJEnemyStatComponent()
{
	/*
	 * Minjin
	 * TODO
	 * 우선은 1로 하는데, 캐릭터마다 다르게 설정해야 됨. 생각해보기
	 */
	EnemyLevel = 1;
}

void UMJEnemyStatComponent::InitializeStat()
{
	bIsInitializingStats = true;

	AMJMonsterCharacter* OwnerCharacter = Cast<AMJMonsterCharacter>(GetOwner());
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

	for (const auto& CurveTableRow : EnemyStatTable->GetRowMap())
	{
		const FName& RowName = CurveTableRow.Key;
		FRealCurve* Curve = EnemyStatTable->FindCurve(RowName, TEXT("FindCurve"));
		if (Curve)
		{
			float Value = Curve->Eval(EnemyLevel);
			FString TagString = FString::Printf(TEXT("Data.Character.%s"), *RowName.ToString());
			SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName(*TagString)), Value);
		}
	}
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = ASC->GetSet<UMJCharacterAttributeSet>()->GetMaxMovementSpeed();

	bIsInitializingStats = false;
}
