#include "MJCharacterAttributeSaveDataStruct.h"

FMJCharacterAttributeSaveData& FMJCharacterAttributeSaveData::operator=(const UMJCharacterAttributeSet& AttributeSet)
{
// Stat | Level
	Level = AttributeSet.GetLevel();
	MaxLevel = AttributeSet.GetMaxLevel();
	Experience = AttributeSet.GetExperience();
	MaxExperience = AttributeSet.GetMaxExperience();
	DropExperience = AttributeSet.GetDropExperience();
	MaxDropExperience = AttributeSet.GetMaxDropExperience();

	// Stat | Resource
	Health = AttributeSet.GetHealth();
	MaxHealth = AttributeSet.GetMaxHealth();
	HealthRegeneration = AttributeSet.GetHealthRegeneration();
	MaxHealthRegeneration = AttributeSet.GetMaxHealthRegeneration();

	Stamina = AttributeSet.GetStamina();
	MaxStamina = AttributeSet.GetMaxStamina();
	StaminaRegeneration = AttributeSet.GetStaminaRegeneration();
	MaxStaminaRegeneration = AttributeSet.GetMaxStaminaRegeneration();

	Mana = AttributeSet.GetMana();
	MaxMana = AttributeSet.GetMaxMana();
	ManaRegeneration = AttributeSet.GetManaRegeneration();
	MaxManaRegeneration = AttributeSet.GetMaxManaRegeneration();

	Focus = AttributeSet.GetFocus();
	MaxFocus = AttributeSet.GetMaxFocus();
	FocusRegeneration = AttributeSet.GetFocusRegeneration();
	MaxFocusRegeneration = AttributeSet.GetMaxFocusRegeneration();

	// Attack / Ability
	AttackDamage = AttributeSet.GetAttackDamage();
	MaxAttackDamage = AttributeSet.GetMaxAttackDamage();
	AbilityPower = AttributeSet.GetAbilityPower();
	MaxAbilityPower = AttributeSet.GetMaxAbilityPower();

	// Armor / Resistance
	Armor = AttributeSet.GetArmor();
	MaxArmor = AttributeSet.GetMaxArmor();
	Resistance = AttributeSet.GetResistance();
	MaxResistance = AttributeSet.GetMaxResistance();

	// Attack Speed
	AttackSpeed = AttributeSet.GetAttackSpeed();
	MaxAttackSpeed = AttributeSet.GetMaxAttackSpeed();

	// Skill Cooldown
	SkillCooldown = AttributeSet.GetSkillCooldown();
	MaxSkillCooldown = AttributeSet.GetMaxSkillCooldown();

	// Critical
	CriticalChance = AttributeSet.GetCriticalChance();
	MaxCriticalChance = AttributeSet.GetMaxCriticalChance();
	CriticalDamage = AttributeSet.GetCriticalDamage();
	MaxCriticalDamage = AttributeSet.GetMaxCriticalDamage();

	// Movement Speed
	MovementSpeed = AttributeSet.GetMovementSpeed();
	MaxMovementSpeed = AttributeSet.GetMaxMovementSpeed();

	// Damage
	Damage = AttributeSet.GetDamage();

	return *this;
}

void FMJCharacterAttributeSaveData::ApplyToAttributeSet(UMJCharacterAttributeSet& AttributeSet) const
{
	// Stat | Level
	AttributeSet.SetLevel(Level);
	AttributeSet.SetMaxLevel(MaxLevel);
	AttributeSet.SetExperience(Experience);
	AttributeSet.SetMaxExperience(MaxExperience);
	AttributeSet.SetDropExperience(DropExperience);
	AttributeSet.SetMaxDropExperience(MaxDropExperience);

	// Stat | Resource
	AttributeSet.SetHealth(Health);
	AttributeSet.SetMaxHealth(MaxHealth);
	AttributeSet.SetHealthRegeneration(HealthRegeneration);
	AttributeSet.SetMaxHealthRegeneration(MaxHealthRegeneration);

	AttributeSet.SetStamina(Stamina);
	AttributeSet.SetMaxStamina(MaxStamina);
	AttributeSet.SetStaminaRegeneration(StaminaRegeneration);
	AttributeSet.SetMaxStaminaRegeneration(MaxStaminaRegeneration);

	AttributeSet.SetMana(Mana);
	AttributeSet.SetMaxMana(MaxMana);
	AttributeSet.SetManaRegeneration(ManaRegeneration);
	AttributeSet.SetMaxManaRegeneration(MaxManaRegeneration);

	AttributeSet.SetFocus(Focus);
	AttributeSet.SetMaxFocus(MaxFocus);
	AttributeSet.SetFocusRegeneration(FocusRegeneration);
	AttributeSet.SetMaxFocusRegeneration(MaxFocusRegeneration);

	// Attack / Ability
	AttributeSet.SetAttackDamage(AttackDamage);
	AttributeSet.SetMaxAttackDamage(MaxAttackDamage);
	AttributeSet.SetAbilityPower(AbilityPower);
	AttributeSet.SetMaxAbilityPower(MaxAbilityPower);

	// Armor / Resistance
	AttributeSet.SetArmor(Armor);
	AttributeSet.SetMaxArmor(MaxArmor);
	AttributeSet.SetResistance(Resistance);
	AttributeSet.SetMaxResistance(MaxResistance);

	// Attack Speed
	AttributeSet.SetAttackSpeed(AttackSpeed);
	AttributeSet.SetMaxAttackSpeed(MaxAttackSpeed);

	// Skill Cooldown
	AttributeSet.SetSkillCooldown(SkillCooldown);
	AttributeSet.SetMaxSkillCooldown(MaxSkillCooldown);

	// Critical
	AttributeSet.SetCriticalChance(CriticalChance);
	AttributeSet.SetMaxCriticalChance(MaxCriticalChance);
	AttributeSet.SetCriticalDamage(CriticalDamage);
	AttributeSet.SetMaxCriticalDamage(MaxCriticalDamage);

	// Movement Speed
	AttributeSet.SetMovementSpeed(MovementSpeed);
	AttributeSet.SetMaxMovementSpeed(MaxMovementSpeed);

	// Damage
	AttributeSet.SetDamage(Damage);
}

