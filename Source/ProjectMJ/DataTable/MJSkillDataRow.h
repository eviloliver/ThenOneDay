
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "MJSkillDataRow.generated.h"

/**
 * Class Description: DataTable Base
 * Author: 신동민
 * Created Date: 2025.06.27
 * Description of Change: Ability 부분 수정
 * Modified By: 신동민
 * Modified Date: 2025.08.06
 */

class AMJProjectileBase;
class UGameplayAbility;
class UCurveTable;

UENUM(BlueprintType)
enum class ERequiredWeapon : uint8
{
	None  UMETA(Hidden),
	MeleeWeapon UMETA(DisplayName = "MeleeWeapon", ToolTip = "Sword, Spear, Dagger, ..."),
	RangeWeapon UMETA(DisplayName = "RangeWeapon", ToolTip = "Bow, Cross bow, Gun, ..."),
	MagicWeapon UMETA(DisplayName = "MagicWeapon", ToolTip = "Staff, Orb, Wand, ..."),
	Anything UMETA(DisplayName = "Anything", ToolTip = "Anything"),
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	None UMETA(Hidden),
	Instant UMETA(DisplayName = "Instant", ToolTip = "Instantly Action Skill"),
	Charge UMETA(DisplayName = "Charge", ToolTip = "Charging Action Skill"),
	Passive UMETA(DisplayName = "Passive", ToolTip = "Passive Skill"),
};

UENUM(BlueprintType)
enum class ESkillTargetType : uint8
{
	None    UMETA(Hidden),
	Single  UMETA(DisplayName = "Single", ToolTip = "Single Target"),
	Area    UMETA(DisplayName = "AoE", ToolTip = "Area of Effect"),
};

USTRUCT(BlueprintType)
struct FMJSkillDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	// Dongmin: RowName을 태그와 같게 할 목적
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Skill"))
	FGameplayTag DefaultSkillTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERequiredWeapon RequiredWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillType SkillType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillTargetType SkillTargetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UCurveTable> SkillLevelDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataTable> SkillLevelAbilityTable;
};