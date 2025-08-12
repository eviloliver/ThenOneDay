// ThenOneDayStudio


#include "Character/Component/MJEnemySkillComponent.h"

#include "ProjectMJ.h"
#include "DataTable/MJEnemyDataRow.h"
#include "Kismet/KismetMathLibrary.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "TG/MJGameInstanceTG.h"

UMJEnemySkillComponent::UMJEnemySkillComponent()
{

}

void UMJEnemySkillComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
	if (!GI || !GI->EnemyDataTable)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist GI or EnemyDataTable"));
		return;
	}

	AMJMonsterCharacter* Enemy = Cast<AMJMonsterCharacter>(GetOwner());
	if (Enemy == nullptr)
	{
		MJ_LOG(LogMJ, Error, TEXT("Owner is Not Exist"));
		return;
	}
	
	const FMJEnemyDataRow* DataRow = GI->EnemyDataTable->FindRow<FMJEnemyDataRow>(Enemy->GetDefaultEnemyTag().GetTagName(), TEXT("Find EnemyData"));
	if (!DataRow)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist DataRow"));
		return;
	}

	/*
	 * Minjin
	 * TODO
	 * 몬스터의 레벨에 따라 스킬 레벨도 다르게 적용하기?-색깔 다르게 할까ㅎㅎ
	 */
	// Minjin: 기본 공격
	LearnSkill(DataRow->NormalAttackTag);
	EquipSkill(DataRow->NormalAttackTag);

	// Minjin: 특수 공격 -> 드랍하는 스킬
	LearnSkill(DataRow->IdentitySkillTag);
	EquipSkill(DataRow->IdentitySkillTag);
	
	// Minjin: Activate 때 사용할 수 있도록 스킬 태그를 저장
	NormalSkillTag = DataRow->NormalAttackTag;
	IdentitySkillTag = DataRow->IdentitySkillTag;

	// Minjin: 죽었을 때 스킬을 전달할 확률
	GiveChance = DataRow->GiveChance;
}

void UMJEnemySkillComponent::BeginPlay()
{
	Super::BeginPlay();
}

UDataTable* UMJEnemySkillComponent::GetSkillDataTable() const
{
	UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
	if (!GI)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist GI"));
		return nullptr;
	}
	UDataTable* SkillDataTable = GI->EnemySkillDataTable;
	if (!SkillDataTable)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist SkillDataTable"));
		return nullptr;
	}
	return SkillDataTable;
}

void UMJEnemySkillComponent::ActivateNormalSkill()
{
	ActivateSkill(NormalSkillTag);
}

void UMJEnemySkillComponent::ActivateIdentitySkill()
{
	ActivateSkill(IdentitySkillTag);
}

FGameplayTag UMJEnemySkillComponent::TryGiveMemory()
{
	if(!IdentitySkillTag.IsValid())
	{
		return FGameplayTag::EmptyTag;
	}

	bool IsCanGive = UKismetMathLibrary::RandomBoolWithWeight(GiveChance);

	if (IsCanGive)
	{
		return IdentitySkillTag;
	}
	
	return FGameplayTag::EmptyTag;
}
