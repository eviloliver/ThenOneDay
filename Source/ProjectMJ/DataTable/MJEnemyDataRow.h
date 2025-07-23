
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "MJEnemyDataRow.generated.h"

/**
 * Class Description: Enemy DataTable Base
 * Author: 신동민
 * Created Date: 2025.07.16
 * Modified By:
 * Modified Date:
 */

class AMJMonsterAIControllerBase;
class UCurveTable;
class USkeletalMesh;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FMJEnemyDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Enemy.Name"))
	FGameplayTag DefaultEnemyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Enemy.Type"))
	FGameplayTag TypeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Enemy.Species"))
	FGameplayTag SpeciesTag;

	// 배우고 있는 스킬 관련
	// Skill Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Skill.Normal"))
	FGameplayTag NormalAttackTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Skill"))
	FGameplayTag IdentitySkillTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillLevel = 1;

	// 기본 스탯
	// Basic Stat Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UCurveTable> AttributeCurve;

	// TODO: 사운드나 아이콘 등등

	// Minjin: Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimationAsset> AppearanceAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimationAsset> DeathAnimation;
	
	/*
	 * TODO
	 * 비헤이비어트리, AIController
	 */
	// AIController
	
	// BehaviorTree
	
	// 초기 세팅값
	// Initial Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

};