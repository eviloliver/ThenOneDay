// Fill out your copyright notice in the Description page of Project Settings.


#include "MJCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "ProjectMJ.h"
#include "Character/MJCharacterBase.h"
#include "Character/Component/MJStatComponentBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "Perception/AISense_Damage.h"

UMJCharacterAttributeSet::UMJCharacterAttributeSet()
    : Experience(0.0f)
	, MaxExperience(999999.0f)
	, DropExperience(0.0f)
	, MaxDropExperience(999.0f)

	, Health(100.0f)
	, MaxHealth(100.0f)
	, HealthRegeneration(0.0f)
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

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	else if (Attribute == GetFocusAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxFocus());
	}
	//
	else if (Attribute == GetExperienceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxExperience());
	}
	else if (Attribute == GetDropExperienceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxDropExperience());
	}
	//
	else if (Attribute == GetAttackSpeedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxAttackSpeed());
	}
	else if (Attribute == GetSkillCooldownAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxSkillCooldown());
	}
	else if (Attribute == GetResistanceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxResistance());
	}
	else if (Attribute == GetMovementSpeedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMovementSpeed());
	}

}

void UMJCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Attribute == GetMaxStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	else if (Attribute == GetMaxFocusAttribute())
	{
		SetFocus(FMath::Clamp(GetFocus(), 0.f, GetMaxFocus()));
	}
	//
	else if (Attribute == GetMaxExperienceAttribute())
	{
		SetExperience(FMath::Clamp(GetExperience(), 0.f, GetMaxExperience()));
	}
	else if (Attribute == GetMaxDropExperienceAttribute())
	{
		SetDropExperience(FMath::Clamp(GetDropExperience(), 0.f, GetMaxDropExperience()));
	}
	//
	else if (Attribute == GetMaxAttackSpeedAttribute())
	{
		SetAttackSpeed(FMath::Clamp(GetAttackSpeed(), 0.f, GetMaxAttackSpeed()));
	}
	else if (Attribute == GetMaxSkillCooldownAttribute())
	{
		SetSkillCooldown(FMath::Clamp(GetSkillCooldown(), 0.f, GetMaxSkillCooldown()));
	}
	else if (Attribute == GetMaxResistanceAttribute())
	{
		SetResistance(FMath::Clamp(GetResistance(), 0.f, GetMaxResistance()));
	}
	else if (Attribute == GetMaxMovementSpeedAttribute())
	{
		SetMovementSpeed(FMath::Clamp(GetMovementSpeed(), 0.f, GetMaxMovementSpeed()));
	}

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

	if (Data.Target.GetAvatarActor() == nullptr)
	{
		return;
	}

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
				bool bIsCritical;
				FGameplayTag IsCriticalTag = FGameplayTag::RequestGameplayTag(FName("Data.Character.IsCritical"));
				if (Data.EffectSpec.GetDynamicAssetTags().HasTag(IsCriticalTag))
				{
					bIsCritical = true;
				}
				else
				{
					bIsCritical = false;
				}
				StatComp->OnDamaged(Data.EvaluatedData.Magnitude, bIsCritical);

				// Minjin: Damage Perception - Data 사용함. TODO.위치 수정하기
				// EventLocation으로 들어가는 값이 Stimulus Location이다.- HitResult값이 nullptr이라서 Target의 Location 넣어놓음
				AActor* Target = Data.Target.GetAvatarActor();
				FVector TargetLocation = Target->GetActorLocation();
				UAISense_Damage::ReportDamageEvent(Target->GetWorld(), Target,
					Data.EffectSpec.GetEffectContext().GetEffectCauser(), Data.EvaluatedData.Magnitude,
					Target->GetActorLocation(), FVector::Zero()/*Data.EffectSpec.GetEffectContext().GetHitResult()->Location*/
					);

				// Minjin: Damage Ability
				AMJCharacterBase* Character = Cast<AMJCharacterBase>(Target);
				if (Character == nullptr)
				{
					return;
				}
				FGameplayTag DamageTag = FGameplayTag::RequestGameplayTag(FName("Character.State.IsHurt"));
				if (Data.EffectSpec.GetDynamicAssetTags().HasTag(DamageTag))
				{
					FGameplayEventData EventData;
					EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Character.Hurt"));
					Character->ASC->HandleGameplayEvent(EventData.EventTag, &EventData);
				}
			}
		}

	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	else if (Data.EvaluatedData.Attribute == GetFocusAttribute())
	{
		SetFocus(FMath::Clamp(GetFocus(), 0.f, GetMaxFocus()));
	}
	//
	else if (Data.EvaluatedData.Attribute == GetExperienceAttribute())
	{
		SetExperience(FMath::Clamp(GetExperience(), 0.f, GetMaxExperience()));
	}
	else if (Data.EvaluatedData.Attribute == GetDropExperienceAttribute())
	{
		SetDropExperience(FMath::Clamp(GetDropExperience(), 0.f, GetMaxDropExperience()));
	}
	//
	else if (Data.EvaluatedData.Attribute == GetAttackSpeedAttribute())
	{
		SetAttackSpeed(FMath::Clamp(GetAttackSpeed(), 0.f, GetMaxAttackSpeed()));
	}
	else if (Data.EvaluatedData.Attribute == GetSkillCooldownAttribute())
	{
		SetSkillCooldown(FMath::Clamp(GetSkillCooldown(), 0.f, GetMaxSkillCooldown()));
	}
	else if (Data.EvaluatedData.Attribute == GetResistanceAttribute())
	{
		SetResistance(FMath::Clamp(GetResistance(), 0.f, GetMaxResistance()));
	}
	else if (Data.EvaluatedData.Attribute == GetMovementSpeedAttribute())
	{
		SetMovementSpeed(FMath::Clamp(GetMovementSpeed(), 0.f, GetMaxMovementSpeed()));
	}

	// 이동속도 변경 바로 반영
	if(Data.EvaluatedData.Attribute == GetMaxMovementSpeedAttribute() || Data.EvaluatedData.Attribute == GetMovementSpeedAttribute())
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