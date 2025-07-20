// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJMonsterCharacter.h"

#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "Character/Component/MJEnemyStatComponent.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "DataAsset/DataAsset_StartDataBase.h"
#include "DataTable/MJEnemyDataRow.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TG/MJGameInstanceTG.h"

AMJMonsterCharacter::AMJMonsterCharacter()
{
	//AIControllerClass = AMJAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	// RVO
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 100.0f;

	// Minjin: 캐릭터의 회전을 부드럽게 해줌
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	bUseControllerRotationYaw = false;
	
	// GAS, Attr Set
	ASC = CreateDefaultSubobject<UMJAbilitySystemComponent>(TEXT("ASC"));
	
	CharacterAttributeSet = CreateDefaultSubobject<UMJCharacterAttributeSet>(TEXT("CharacterAttributeSet"));

	// Stat Component
	StatComponent = CreateDefaultSubobject<UMJEnemyStatComponent>(TEXT("StatComponent"));

	CharacterSkillAttributeSet = CreateDefaultSubobject<UMJCharacterSkillAttributeSet>(TEXT("CharacterSkillAttributeSet"));

	// Skill Component
	SkillComponent = CreateDefaultSubobject<UMJSkillComponentBase>(TEXT("SkillComponent"));
}

void AMJMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Minjin: 캐릭터는 미리 맵에 스폰되어 있다. 안 보이게 설정-콜리전을 비활성화 하면 맵 밑으로 꺼짐
	AActor::SetActorHiddenInGame(true);
	SetActorEnableCollision(true);
}

float AMJMonsterCharacter::GetAIPatrolRadius()
{
	return 800.0f;
}

float AMJMonsterCharacter::GetAITurnSpeed()
{
	return 5.0f;
}

float AMJMonsterCharacter::GetAIMaximumAttackRange()
{
	// Minjin: 원거리 공격(근거리 몬스터의 경우 중거리 공격으로 활용 가능할 듯)
	/*
	* TODO
	* 우선 하드코딩. 스탯 기반으로 바꾸기
	*/
	//return Stat->GetTotalStat().AttackRange + Stat->GetAttackRadius()*2;
	return 500.0f;
}

float AMJMonsterCharacter::GetAIMinimumAttackRange()
{
	// Minjin: 근거리 공격
	/*
	* TODO
	* 우선 하드코딩. 스탯 기반으로 바꾸기
	*/
	//return Stat->GetTotalStat().AttackRange + Stat->GetAttackRadius()*2;
	return 200.0f;
}

void AMJMonsterCharacter::AttackByAI()
{
	/*
	 * TODO
	 * 공격
	 */
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Attack"));
}

void AMJMonsterCharacter::MeleeAttackByAI()
{
	/*
	 * Minjin
	 * TODO
	 * 근거리 공격
	 */
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("MeleeAttack"));
}

void AMJMonsterCharacter::RangeAttackByAI()
{
	/*
 * Minjin
 * TODO
 * 원거리 공격
 */
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("RangeAttack"));
}

UAbilitySystemComponent* AMJMonsterCharacter::GetAbilitySystemComponent() const
{
	if (ASC)
	{
		return ASC;
	}
	return nullptr;
}

void AMJMonsterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	CharacterAttributeSet->OnDeath.AddDynamic(this, &ThisClass::OnDeath);
	
	if (ASC)
	{
		ASC->InitAbilityActorInfo(this,this);
	}

	if (!CharacterStartData.IsNull())
	{
		if (UDataAsset_StartDataBase* LoadData = CharacterStartData.LoadSynchronous())
		{
			LoadData->GiveToAbilitySystemComponent(Cast<UMJAbilitySystemComponent>(GetAbilitySystemComponent()));
		}
	}
	
	// TODO:
	// 여기서 DT 받아와서 Attribute랑 몬스터가 가지고 있는 스킬 넣을거야
	// 그래서 이 몬스터를 구븐 할 수 있는 RowName이 Tag인 형식의 DT와
	// RowName이랑 똑같은 이름의 Tag(ex- Enemy.Dongmin)를 속성에서 가지고 있어서 BP로 양산할 때 넣는거야
	// 그런데 자동으로 DT에 있는 값으로 Attribute를 넣어 줄 거면 전체 덮어주는 Effect 가지고 있고, 노가다가 필요해서
	// 나중에 DT만들고 집중 안될 때 와서 작업 함
	//  -동민 -
	// 알겠긔 -민진-

	/*
	* Minjin
	* EnemyDataTable을 통해 스탯 초기화
	* 기본 태그와 행이름이 동일. 기본 태그를 통해 행을 가져온다. 기본 태그는 BP에서 설정
	*/
	UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
	if (!GI || !GI->EnemyDataTable)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist GI or EnemyDataTable"));
		return;
	}

	const FMJEnemyDataRow* DataRow = GI->EnemyDataTable->FindRow<FMJEnemyDataRow>(DefaultEnemyTag.GetTagName(), TEXT("Find EnemyData"));
	if (!DataRow)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist DataRow"));
		return;
	}

	// Minjin: 기본 공격
	//SkillComponent->LearnSkill(DataRow->NormalAttackTag);
	//SkillComponent->EquipSkill(DataRow->NormalAttackTag);

	// Minjin: 특수 공격 -> 드랍하는 스킬
	SkillComponent->LearnSkill(DataRow->IdentitySkillTag);
	SkillComponent->EquipSkill(DataRow->IdentitySkillTag);

	// Minjin: Attribute Setting
	if (StatComponent)
	{
		UCurveTable* AttributeCurve = DataRow->AttributeCurve.LoadSynchronous();
		if (!AttributeCurve)
		{
			MJ_LOG(LogMJ, Log, TEXT("Not Exist AttributeCurve"));
			return;
		}
		
		StatComponent->SetStatTable(AttributeCurve);
		StatComponent->InitializeStat();
	}
}

void AMJMonsterCharacter::OnDeath()
{
	// TODO:
	// 애니메이션과 기타 등등 세팅
	// - 동민 -
	Destroy();

}
