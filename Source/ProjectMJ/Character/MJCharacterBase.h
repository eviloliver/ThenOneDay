// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "MJ/AI/AIPerceptionInfo.h"
#include "MJCharacterBase.generated.h"

class UMJDamageComponent;
class UMJStateAbilityDataAsset;
class UMJAbilityContextComponent;
class UMJMiniMapIconMeshComponent;
class AMJMiniMapIconActor;
class UMJAbilitySystemComponent;
class UMJAttributeSet;
class UDataAsset_StartDataBase;
class UMotionWarpingComponent;
/**
 * Class Description: CharacterBased
 * Author: Lee JuHyeon
 * Created Date: 2025_06_11
 * Modified By: Lee JuHyeon / Kim Minjin
 * Modified Date: Add DA_StartData / (2025.06.20.)Inheritance from IGenericTeamAgentInterface
 * 
 * Description of Change: 모션 워핑 컴포넌트 추가
 * Modified By: 신동민	
 * Modified Date: 2025.07.19
 * 
 * Description of Change: add MiniMapIconMeshComponent 
 * Modified By: CTG	
 * Modified Date: 2025.07.31
 *
 * Description of Change: Add StateAbilityDataAsset And Setting
 * Modified By: Kim Minjin	
 * Modified Date: 2025.08.09.
 */
UENUM(BlueprintType)
enum class EOwnerType : uint8
{
	Player,
	Monster
};

UCLASS()
class PROJECTMJ_API AMJCharacterBase : public ACharacter , public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMJCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UMJMiniMapIconMeshComponent* GetMiniMapIconMeshComponent() {return MiniMapIconMeshComponent;}

	// GenericTeamAgentInterface 구현
	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;}
	// 에디터에서 ID 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ID")
	ETeam_ID ID = ETeam_ID::NONE;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UMJAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSoftObjectPtr<UDataAsset_StartDataBase>CharacterStartData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GAS")
	TObjectPtr<UMJStateAbilityDataAsset> StateAbilityDataAsset;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GAS")
	TObjectPtr<UMJAbilityContextComponent> AbilityContextComponent;
  
protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UMJMiniMapIconMeshComponent> MiniMapIconMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UMJDamageComponent>> DamageComponents;
	
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController)override;

	FGenericTeamId TeamId;

public:
	// jisoo
	UFUNCTION()
	virtual void FloatDamage(float Magnitude, bool bIsCritical, EOwnerType type);
	float OffSet = 0;
};


