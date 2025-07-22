// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJMonsterCharacter.h"

#include "UI/World/MJDamageComponent.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "DataAsset/DataAsset_StartDataBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/World/MJDamageWidget.h"
#include "UI/MJUIManagerSubsystem.h"

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

	CharacterSkillAttributeSet = CreateDefaultSubobject<UMJCharacterSkillAttributeSet>(TEXT("CharacterSkillAttributeSet"));

	// Skill Component
	SkillComponent = CreateDefaultSubobject<UMJSkillComponentBase>(TEXT("SkillComponent"));

	// UI Component
	HPBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarComponent"));
	HPBarComponent->SetupAttachment(GetMesh());
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
	CharacterAttributeSet->OnDeath.AddDynamic(this, &ThisClass::OnDeath);
}

void AMJMonsterCharacter::OnDeath()
{
	// TODO:
	// 애니메이션과 기타 등등 세팅
	// - 동민 -
	Destroy();
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
