// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJMonsterCharacter.h"

#include "UI/World/MJDamageComponent.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "Character/MJPlayerCharacter.h"
#include "Character/Component/MJEnemySkillComponent.h"
#include "Character/Component/MJEnemyStatComponent.h"
#include "DataAsset/DataAsset_StartDataBase.h"
#include "DataTable/MJEnemyDataRow.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MJ/AI/MJMonsterAIControllerBase.h"
#include "Components/WidgetComponent.h"
#include "UI/World/MJDamageWidget.h"
#include "UI/MJUIManagerSubsystem.h"
#include "TG/MJGameInstanceTG.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "DataAsset/MJStateAbilityDataAsset.h"
#include "Item/MJItemBase.h"
#include "MJ/DataAssetMJ/MJDropItemsDataAsset.h"
#include "UI/Inventory/ItemDataRow.h"
#include "UI/Bar/MJEnemyHPBar.h"
#include "UI/Component/MJHealthBarComponent.h"

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
	SkillComponent = CreateDefaultSubobject<UMJEnemySkillComponent>(TEXT("SkillComponent"));

	// UI Component
	HPBarComponent = CreateDefaultSubobject<UMJHealthBarComponent>(TEXT("HPBarComponent"));
	HPBarComponent->SetupAttachment(GetRootComponent());

	// Minjin: ID 설정
	ID = ETeam_ID::MONSTER;
}

void AMJMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Minjin: 캐릭터는 미리 맵에 스폰되어 있다. 안 보이게 설정-콜리전을 비활성화 하면 맵 밑으로 꺼짐
	// AActor::SetActorHiddenInGame(true);
	// SetActorEnableCollision(true);
	
	// Jisoo
	if (UMJEnemyHPBar* EnemyHPBar = Cast<UMJEnemyHPBar>(HPBarComponent->GetUserWidgetObject()))
	{
		EnemyHPBar->BindToAttributes(ASC,CharacterAttributeSet);
	}
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
	StatComponent->OnDamage.AddDynamic(this,&ThisClass::OnDamage);
	StatComponent->OnDeath.AddDynamic(this, &ThisClass::OnDead);
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
	
	// Minjin: Attribute Setting
	UCurveTable* AttributeCurve = DataRow->AttributeCurve.LoadSynchronous();
	if (!AttributeCurve)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist AttributeCurve"));
		return;
	}
		
	StatComponent->SetStatTable(AttributeCurve);
	StatComponent->InitializeStat();

	SkillComponent->InitializeComponent();
	
	// Minjin: Animation Setting
	AppearanceAnimation = DataRow->AppearanceAnimation;
	DeathAnimation = DataRow->DeathAnimation;

	// // Minjin: 죽었을 때 전달할 정보 Setting-SkillComponent에서 얻어온다.
	EnemyBequest.IdentitySkillTag = SkillComponent->TryGiveMemory();
	EnemyBequest.Exp = ASC->GetSet<UMJCharacterAttributeSet>()->GetDropExperience();

	// Minjin: 지정한 확률로 아이템 태그를 얻음
	EnemyBequest.ItemTag = DataRow->DropItems->TryDropItem();

	/*
	 * Minjin
	 * StateAbilityDataAsset 설정
	 */
	UMJStateAbilityDataAsset* StateAbility = DataRow->StateAbility;
	if (!StateAbility)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist StateAbility"));
		return;
	}
	
	StateAbilityDataAsset = StateAbility;
}

void AMJMonsterCharacter::GiveDeathRewardTo()
{
	// Minjin: 애니메이션 재생되는 동안 경험치 전달
	AMJPlayerCharacter* Player = Cast<AMJPlayerCharacter>(EnemyBequest.Target);
	if (Player)
	{
		Player->StatComponent->GainExperience(EnemyBequest.Exp);
		MJ_LOG(LogMJ, Warning, TEXT("경험치 전달: %d"), EnemyBequest.Exp);
	}

	if (EnemyBequest.ItemTag.IsValid())
	{
		UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
		if (!GI || !GI->ItemDataTable)
		{
			MJ_LOG(LogMJ, Error, TEXT("Not Exist GI or ItemDataTable"));
			return;
		}

		const FItemDataRow* DataRow = GI->ItemDataTable->FindRow<FItemDataRow>(EnemyBequest.ItemTag.GetTagName(), TEXT("Find ItemData"));
		if (!DataRow)
		{
			MJ_LOG(LogMJ, Error, TEXT("Not Exist DataRow"));
			return;
		}

		TSubclassOf<AMJItemBase> ItemClass = DataRow->ItemClass;
		if (ItemClass)
		{
			FVector SpawnLocation = GetActorLocation();
			SpawnLocation.Z = 0.0f;
			FTransform SpawnTransform(SpawnLocation);
			AMJItemBase* Item = GetWorld()->SpawnActorDeferred<AMJItemBase>(ItemClass, SpawnTransform);
			// Item->SetActorEnableCollision(false);
			Item->FinishSpawning(SpawnTransform);
		}
	}
}

void AMJMonsterCharacter::OnDead(AActor* InEffectCauser)
{
	if (bIsDying)
	{
		MJ_LOG(LogMJ, Warning, TEXT("%s: 죽는 중..."), *GetName());
		return;
	}
	
	MJ_LOG(LogMJ, Warning, TEXT("%s: Death Start"), *GetName());
	// TODO:
	// 애니메이션과 기타 등등 세팅
	// - 동민 -

	bIsDying = true;

	// Minin: Target 정보 저장
	EnemyBequest.Target = InEffectCauser;
	
	AMJMonsterAIControllerBase* AIController = Cast<AMJMonsterAIControllerBase>(GetController());
	if (AIController)
	{
		AIController->StopAI();
	}

	// Minjin: Death Ability
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Character.Dead"));
	ASC->HandleGameplayEvent(EventData.EventTag, &EventData);
	
	DamageIndex = 0;
}

void AMJMonsterCharacter::OnDamage(float Magnitude, bool bIsCritical)
{	
	HPBarComponent->SetVisibility(true);

	FloatDamage(Magnitude, bIsCritical, EOwnerType::Monster);
}
