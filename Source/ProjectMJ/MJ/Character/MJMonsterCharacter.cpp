// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJMonsterCharacter.h"

#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	return 2.0f;
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
}
