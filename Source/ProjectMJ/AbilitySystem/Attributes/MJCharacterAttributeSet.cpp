// Fill out your copyright notice in the Description page of Project Settings.


#include "MJCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "ProjectMJ.h"
#include "Character/MJCharacterBase.h"
#include "Character/Component/MJStatComponentBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UMJCharacterAttributeSet::UMJCharacterAttributeSet()
    : Experience(0.0f)
	, MaxExperience(999999.0f)
	, DropExperience(0.0f)
	, MaxDropExperience(999.0f)

	, Health(100.0f)
	, MaxHealth(100.0f)
	, HealthRegeneration(0.0f)
	, MaxHealthRegeneration(100.0f)
	, Stamina(100.0f)
	, MaxStamina(100.0f)
	, StaminaRegeneration(0.0f)
	, Mana(100.0f)
	, MaxMana(100.0f)
	, ManaRegeneration(0.0f)
	, Focus(100.0f)
	, MaxFocus(100.0f)
	, FocusRegeneration(0.0f)

	, AttackDamage(10.0f)
	, AbilityPower(10.0f)
	, Armor(0.0f)
	, Resistance(0.0f)
	, MaxResistance(999.0f)

	, AttackSpeed(1.0f)
	, MaxAttackSpeed(10.0f)
	, SkillCooldown(1.0f)
	, MaxSkillCooldown(0.0f)

	, CriticalChance(0.0f)
	, CriticalDamage(0.0f)

	, MovementSpeed(600.0f)
	, MaxMovementSpeed(1200.0f)

{
	InitHealth(GetMaxHealth());
	InitStamina(GetMaxStamina());
	InitMana(GetMaxMana());
	InitFocus(GetMaxFocus());
}

void UMJCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UMJCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

}

bool UMJCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	return true;
		
}

void UMJCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	// Effect 적용 후

	if (UMJStatComponentBase* StatComp = Data.Target.GetAvatarActor()->FindComponentByClass<UMJStatComponentBase>())
	{
		if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		{
			if (GetHealth() <= 0)
			{
				if (!StatComp->GetbIsDead())
				{
					// Minjin: 데미지를 입힌 상대 전달
					//StatComp->OnDeath.Broadcast(Data.EffectSpec.GetEffectContext().GetEffectCauser());
					StatComp->OnDead(Data.EffectSpec.GetEffectContext().GetEffectCauser());
				}
			}

			if (Data.EvaluatedData.Magnitude < 0.f) //이렇게 하면 힐이 들어와도 ondamage가 실행되는 불상사를 막을 수 있는 거 같다.!
			{
				const FGameplayEffectSpec& Spec = Data.EffectSpec;
				float IsCritical = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Character.IsCritical")), false, 0.f);
				bool bIsCritical = (IsCritical > 0.5f); // 크리티컬이면 1이 들어가게 설정해둠
				OnDamage.Broadcast(Data.EvaluatedData.Magnitude, bIsCritical);
			}
		}
		else if (Data.EvaluatedData.Attribute == GetMaxMovementSpeedAttribute())
		{
			AMJCharacterBase* Character = Cast<AMJCharacterBase>(Data.Target.GetAvatarActor());
			if (Character)
			{
				UCharacterMovementComponent* MoveComponent = Character->GetCharacterMovement();
				if (MoveComponent)
				{
					MoveComponent->MaxWalkSpeed = GetMaxMovementSpeed();
				}
			}
		}
	}
}