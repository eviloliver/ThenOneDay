// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "MJ/AI/AIPerceptionInfo.h"
#include "MJCharacterBase.generated.h"

class UMJAbilitySystemComponent;
class UMJAttributeSet;
class UDataAsset_StartDataBase;
class UMotionWarpingComponent;
/**
 * Class Description: CharacterBase
 * Author: Lee JuHyeon
 * Created Date: 2025_06_11
 * Modified By: Lee JuHyeon / Kim Minjin
 * Modified Date: Add DA_StartData / (2025.06.20.)Inheritance from IGenericTeamAgentInterface
 * 
 * Description of Change: 모션 워핑 컴포넌트 추가
 * Modified By: 신동민	
 * Modified Date: 2025.07.19
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSoftObjectPtr<UDataAsset_StartDataBase>CharacterStartData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	FGenericTeamId TeamId;
};


