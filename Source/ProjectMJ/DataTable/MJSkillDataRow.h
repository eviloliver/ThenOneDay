
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "MJSkillDataRow.generated.h"

/**
 * Class Description: DataTable Base
 * Author: 신동민
 * Created Date: 2025_06_27
 * Last Modified By:
 * Last Modified Date:
 */

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

class UAnimMontage;
class UCurveTable;

USTRUCT(BlueprintType)
struct FMJSkillDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	// Dongmin: RowName으로 이걸 가져다 쓸거다
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
	TSoftObjectPtr<UAnimMontage> ActionAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UCurveTable> SkillLevelDataTable;

};