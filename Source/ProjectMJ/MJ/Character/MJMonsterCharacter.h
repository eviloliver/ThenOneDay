// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "Character/MJCharacterBase.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "MJMonsterCharacter.generated.h"

class UMJEnemySkillComponent;
class UMJDropItemsDataAsset;
class UMJHealthBarComponent;
class UMJDamageComponent;
class UWidgetComponent;
class UMJEnemyHPBar;
class UMJUIManagerSubsystem;
class UMJEnemyStatComponent;
class UMJCharacterAttributeSet;
class UMJCharacterSkillAttributeSet;
/**
 * Class Description: AICharacter
 * Author: Kim Minjin
 * Created Date: 2025.06.21.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
struct EnemyTransferData
{
	FGameplayTag IdentitySkillTag;
	int32 Exp;
	FGameplayTag ItemTag;
	AActor* Target;
};

UCLASS()
class PROJECTMJ_API AMJMonsterCharacter : public AMJCharacterBase, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	AMJMonsterCharacter();

	FGameplayTag GetAttackTag() {return AttackTag;}
	UMJEnemySkillComponent* GetSkillComponent() {return SkillComponent;}
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	TObjectPtr<UAnimationAsset> GetAppearanceAnimation(){return AppearanceAnimation;}

	const EnemyTransferData& GetEnemyBequest(){return EnemyBequest;}

	const FGameplayTag& GetDefaultEnemyTag() {return DefaultEnemyTag;}

	UFUNCTION()
	virtual void GiveDeathRewardTo();
	
	// IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override
	{
		ASC->GetOwnedGameplayTags(TagContainer);
	}
	
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override
	{
		return ASC->HasMatchingGameplayTag(TagToCheck);
	}
	
	bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override
	{
		return ASC->HasAllMatchingGameplayTags(TagContainer);
	}

	bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override
	{
		return ASC->HasAllMatchingGameplayTags(TagContainer);
	}
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

protected:
	UFUNCTION()
	virtual void OnDead(AActor* InEffectCauser);

	UFUNCTION()
	void OnDamage(float Magnitude, bool bIsCritical);

protected:
	// Jisoo : UI Section
	UPROPERTY()
	TObjectPtr<UMJUIManagerSubsystem> UIManager;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMJHealthBarComponent> HPBarComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UMJDamageComponent>> DamageComponents;
	int DamageIndex = 0;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMJCharacterAttributeSet> CharacterAttributeSet;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMJCharacterSkillAttributeSet> CharacterSkillAttributeSet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gas")
	TObjectPtr<UMJEnemySkillComponent> SkillComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	TObjectPtr<UMJEnemyStatComponent> StatComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Enemy.Name"))
	FGameplayTag DefaultEnemyTag;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool bIsDying = false;

	// Minjin: Animation-안 쓸 예정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimationAsset> AppearanceAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimationAsset> DeathAnimation;
	
	// Minjin: Ability Tag-안씀
	FGameplayTag AttackTag;

	// Minjin: 죽고 플레이어한테 줘야 하는 정보
	EnemyTransferData EnemyBequest;

	FTimerHandle DeadTimerHandle;
};
