// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJMonsterCharacter.h"

#include "UI/World/MJDamageComponent.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "Character/MJPlayerCharacter.h"
#include "Character/Component/MJEnemyStatComponent.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "DataAsset/DataAsset_StartDataBase.h"
#include "DataTable/MJEnemyDataRow.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MJ/AI/MJMonsterAIControllerBase.h"
#include "Components/WidgetComponent.h"
#include "UI/World/MJDamageWidget.h"
#include "UI/MJUIManagerSubsystem.h"
#include "TG/MJGameInstanceTG.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "DataAsset/MJItemDataAsset.h"
#include "Item/MJItemBase.h"
#include "MJ/DataAssetMJ/MJDropItemsDataAsset.h"
#include "UI/Inventory/ItemDataRow.h"

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

	// UI Component
	HPBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarComponent"));
	HPBarComponent->SetupAttachment(GetMesh());

	// Minjin: ID 설정
	ID = ETeam_ID::MONSTER;
}

void AMJMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Minjin: 캐릭터는 미리 맵에 스폰되어 있다. 안 보이게 설정-콜리전을 비활성화 하면 맵 밑으로 꺼짐
	AActor::SetActorHiddenInGame(true);
	SetActorEnableCollision(true);
	
	// Jisoo
	HPBarComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 220.0f));
	HPBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarComponent->SetDrawSize(FVector2D(100.0f,10.0f));
	HPBarComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HPBarComponent->SetVisibility(false);

	UIManager =	GetGameInstance()->GetSubsystem<UMJUIManagerSubsystem>();
	ensure(UIManager);
	UIManager->ResisterWorldUI(HPBarComponent,ASC,CharacterAttributeSet);
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

	CharacterAttributeSet->OnDeath.AddDynamic(this, &ThisClass::OnDead);
	
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
	CharacterAttributeSet->OnDamage.AddDynamic(this,&ThisClass::OnDamage);
	CharacterAttributeSet->OnDeath.AddDynamic(this, &ThisClass::OnDead);
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
	UCurveTable* AttributeCurve = DataRow->AttributeCurve.LoadSynchronous();
	if (!AttributeCurve)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist AttributeCurve"));
		return;
	}
		
	StatComponent->SetStatTable(AttributeCurve);
	StatComponent->InitializeStat();

	// Minjin: Animation Setting
	AppearanceAnimation = DataRow->AppearanceAnimation;
	DeathAnimation = DataRow->DeathAnimation;

	// Minjin: 죽었을 때 전달할 정보 Setting
	EnemyBequest.IdentitySkillTag = DataRow->IdentitySkillTag;
	EnemyBequest.Exp = ASC->GetSet<UMJCharacterAttributeSet>()->GetDropExperience();

	// Minjin: 지정한 확률로 아이템 태그를 얻음
	EnemyBequest.ItemTag = DataRow->DropItems->TryDropItem();
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
	AMJMonsterAIControllerBase* AIController = Cast<AMJMonsterAIControllerBase>(GetController());
	if (AIController)
	{
		AIController->StopAI();
	}
	SetActorEnableCollision(false);
	
	if (DeathAnimation)
	{
		MJ_LOG(LogMJ, Warning, TEXT("%s: Play Death Animation"), *GetName());
		//StopAnimMontage();
		//GetMesh()->PlayAnimation(DeathAnimation, false);<-이거로 하면 공격 들어갈때마다 애니메이션이 처음부터 재생됨
		GetMesh()->OverrideAnimationData(DeathAnimation, false);

		// Minin: Target 정보 저장
		EnemyBequest.Target = InEffectCauser;
		
		const float FinishDelay = DeathAnimation->GetPlayLength();
		FTimerHandle DeadTimerHandle;
		
		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
			[this]()
			{
				SetActorHiddenInGame(true);

				// Minjin: 경험치 전달, 아이템 스폰
				GiveDeathRewardTo();
				
				Destroy();
			}
		), FinishDelay, false);
	}
	else
	{
		SetActorHiddenInGame(true);

		// Minjin: 경험치 전달, 아이템 스폰
		GiveDeathRewardTo();
		
		Destroy();
	}
	DamageIndex = 0;
}

void AMJMonsterCharacter::OnDamage(float Magnitude)
{
	HPBarComponent->SetVisibility(true);
	
	{
		UMJDamageComponent* NewComp = NewObject<UMJDamageComponent>(this);
		NewComp->RegisterComponent();
		NewComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		NewComp->SetWidget();
		NewComp->SetVisibility(true);
		DamageComponents.Add(NewComp);
		
		Cast<UMJDamageWidget>(DamageComponents[DamageIndex]->GetUserWidgetObject())->PlayAnim();
		Cast<UMJDamageWidget>(DamageComponents[DamageIndex]->GetUserWidgetObject())->SetDamage(-Magnitude);

		DamageIndex ++;
	}
}
