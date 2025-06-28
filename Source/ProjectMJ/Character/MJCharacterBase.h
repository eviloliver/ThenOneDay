// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "MJ/AI/AIPerceptionInfo.h"
#include "MJCharacterBase.generated.h"

class UMJAbilitySystemComponent;
class UMJSkillComponent;
class UMJAttributeSet;
class UDataAsset_StartDataBase;
/**
 * Class Description: CharacterBase
 * Author: Lee JuHyeon
 * Created Date: 2025_06_11
 * Last Modified By: Lee JuHyeon / Kim Minjin
 * Last Modified Date: Add DA_StartData / (2025.06.20.)Inheritance from IGenericTeamAgentInterface
 */
UCLASS()
class PROJECTMJ_API AMJCharacterBase : public ACharacter , public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMJCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// GenericTeamAgentInterface 구현
	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;}
	// 에디터에서 ID 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ID")
	ETeam_ID ID = ETeam_ID::NONE;
	
protected:

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController)override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UMJAbilitySystemComponent> ASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Skill")
	TObjectPtr<UMJSkillComponent> SkillComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSoftObjectPtr<UDataAsset_StartDataBase>CharacterStartData;
	
	FGenericTeamId TeamId;
};


