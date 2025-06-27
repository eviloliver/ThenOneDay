#include "MJCharacterSkillAttributeSaveData.h"

// Operator overload
FMJCharacterSkillAttributeSaveData& FMJCharacterSkillAttributeSaveData::operator=(const UMJCharacterSkillAttributeSet& AttributeSet)
{
	// Level
	SkillLevel = AttributeSet.GetSkillLevel();
	MaxSkillLevel = AttributeSet.GetMaxSkillLevel();

	// Cost
	CostStamina = AttributeSet.GetCostStamina();
	MaxCostStamina = AttributeSet.GetMaxCostStamina();
	CostMana = AttributeSet.GetCostMana();
	MaxCostMana = AttributeSet.GetMaxCostMana();
	CostFocus = AttributeSet.GetCostFocus();
	MaxCostFocus = AttributeSet.GetMaxCostFocus();

	// Damage / Scaling
	BaseDamage = AttributeSet.GetBaseDamage();
	MaxBaseDamage = AttributeSet.GetMaxBaseDamage();
	Healing = AttributeSet.GetHealing();
	MaxHealing = AttributeSet.GetMaxHealing();
	LifeSteal = AttributeSet.GetLifeSteal();
	MaxLifeSteal = AttributeSet.GetMaxLifeSteal();
	AttackDamageScaling = AttributeSet.GetAttackDamageScaling();
	MaxAttackDamageScaling = AttributeSet.GetMaxAttackDamageScaling();
	AbilityPowerScaling = AttributeSet.GetAbilityPowerScaling();
	MaxAbilityPowerScaling = AttributeSet.GetMaxAbilityPowerScaling();

	// Range
	SkillRadius = AttributeSet.GetSkillRadius();
	MaxSkillRadius = AttributeSet.GetMaxSkillRadius();
	SkillRange = AttributeSet.GetSkillRange();
	MaxSkillRange = AttributeSet.GetMaxSkillRange();

	// Time
	Cooldown = AttributeSet.GetCooldown();
	MaxCooldown = AttributeSet.GetMaxCooldown();
	SkillAttackRate = AttributeSet.GetSkillAttackRate();
	MaxSkillAttackRate = AttributeSet.GetMaxSkillAttackRate();
	CastTime = AttributeSet.GetCastTime();
	MaxCastTime = AttributeSet.GetMaxCastTime();
	PreDelay = AttributeSet.GetPreDelay();
	MaxPreDelay = AttributeSet.GetMaxPreDelay();
	PostDelay = AttributeSet.GetPostDelay();
	MaxPostDelay = AttributeSet.GetMaxPostDelay();
	EffectDuration = AttributeSet.GetEffectDuration();
	MaxEffectDuration = AttributeSet.GetMaxEffectDuration();

	// Status effect
	StatusEffectChance = AttributeSet.GetStatusEffectChance();
	MaxStatusEffectChance = AttributeSet.GetMaxStatusEffectChance();
	StatusEffectDuration = AttributeSet.GetStatusEffectDuration();
	MaxStatusEffectDuration = AttributeSet.GetMaxStatusEffectDuration();

	// Projectile
	ProjectileSpeed = AttributeSet.GetProjectileSpeed();
	MaxProjectileSpeed = AttributeSet.GetMaxProjectileSpeed();
	ProjectileCount = AttributeSet.GetProjectileCount();
	MaxProjectileCount = AttributeSet.GetMaxProjectileCount();

	return *this;
}

void FMJCharacterSkillAttributeSaveData::ApplyToAttributeSet(UMJCharacterSkillAttributeSet& AttributeSet) const
{
	// Level
	AttributeSet.SetSkillLevel(SkillLevel);
	AttributeSet.SetMaxSkillLevel(MaxSkillLevel);

	// Cost
	AttributeSet.SetCostStamina(CostStamina);
	AttributeSet.SetMaxCostStamina(MaxCostStamina);
	AttributeSet.SetCostMana(CostMana);
	AttributeSet.SetMaxCostMana(MaxCostMana);
	AttributeSet.SetCostFocus(CostFocus);
	AttributeSet.SetMaxCostFocus(MaxCostFocus);

	// Damage / Scaling
	AttributeSet.SetBaseDamage(BaseDamage);
	AttributeSet.SetMaxBaseDamage(MaxBaseDamage);
	AttributeSet.SetHealing(Healing);
	AttributeSet.SetMaxHealing(MaxHealing);
	AttributeSet.SetLifeSteal(LifeSteal);
	AttributeSet.SetMaxLifeSteal(MaxLifeSteal);
	AttributeSet.SetAttackDamageScaling(AttackDamageScaling);
	AttributeSet.SetMaxAttackDamageScaling(MaxAttackDamageScaling);
	AttributeSet.SetAbilityPowerScaling(AbilityPowerScaling);
	AttributeSet.SetMaxAbilityPowerScaling(MaxAbilityPowerScaling);

	// Range
	AttributeSet.SetSkillRadius(SkillRadius);
	AttributeSet.SetMaxSkillRadius(MaxSkillRadius);
	AttributeSet.SetSkillRange(SkillRange);
	AttributeSet.SetMaxSkillRange(MaxSkillRange);

	// Time
	AttributeSet.SetCooldown(Cooldown);
	AttributeSet.SetMaxCooldown(MaxCooldown);
	AttributeSet.SetSkillAttackRate(SkillAttackRate);
	AttributeSet.SetMaxSkillAttackRate(MaxSkillAttackRate);
	AttributeSet.SetCastTime(CastTime);
	AttributeSet.SetMaxCastTime(MaxCastTime);
	AttributeSet.SetPreDelay(PreDelay);
	AttributeSet.SetMaxPreDelay(MaxPreDelay);
	AttributeSet.SetPostDelay(PostDelay);
	AttributeSet.SetMaxPostDelay(MaxPostDelay);
	AttributeSet.SetEffectDuration(EffectDuration);
	AttributeSet.SetMaxEffectDuration(MaxEffectDuration);

	// Status effect
	AttributeSet.SetStatusEffectChance(StatusEffectChance);
	AttributeSet.SetMaxStatusEffectChance(MaxStatusEffectChance);
	AttributeSet.SetStatusEffectDuration(StatusEffectDuration);
	AttributeSet.SetMaxStatusEffectDuration(MaxStatusEffectDuration);

	// Projectile
	AttributeSet.SetProjectileSpeed(ProjectileSpeed);
	AttributeSet.SetMaxProjectileSpeed(MaxProjectileSpeed);
	AttributeSet.SetProjectileCount(ProjectileCount);
	AttributeSet.SetMaxProjectileCount(MaxProjectileCount);
}
