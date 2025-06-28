// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/AI/MJAIControllerBaseTG.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MJ/AI/AIPerceptionInfo.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"

AMJAIControllerBaseTG::AMJAIControllerBaseTG()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	TeamId = 255;

}

void AMJAIControllerBaseTG::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMJAIControllerBaseTG::TargetPerceptionUpdated);

}

void AMJAIControllerBaseTG::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void AMJAIControllerBaseTG::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(BehaviorTreeComponent->GetCurrentTree());
}

void AMJAIControllerBaseTG::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	
}

ETeamAttitude::Type AMJAIControllerBaseTG::GetTeamAttitudeTowards(const AActor& Other) const
{
	ETeamAttitude::Type Result = Super::GetTeamAttitudeTowards(Other);

	/*
	 * How TO: TeamId 비교해서 플레이어, NPC, 몬스터로 나눈다.
	 */

	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (nullptr==OtherPawn)
	{
		return ETeamAttitude::Neutral;
	}

	const IGenericTeamAgentInterface* OtherCharacter = Cast<IGenericTeamAgentInterface> (&Other);
	if (nullptr== OtherCharacter)
	{
		return ETeamAttitude::Neutral;
	}

	FGenericTeamId OtherTeamId = OtherCharacter->GetGenericTeamId();
	if (OtherTeamId == 255)
	{
		// NONE
		return ETeamAttitude::Neutral;
	}
	if (OtherTeamId == 0)
	{
		// 플레이어인 경우
		return ETeamAttitude::Hostile;
	}
	else if ((OtherTeamId>=static_cast<uint8>(ETeam_ID::NPC))&&
		(OtherTeamId<static_cast<uint8>(ETeam_ID::MONSTER)))
	{
		// NPC인 경우
		return ETeamAttitude::Neutral;
	}
	else if (OtherTeamId>=static_cast<uint8>(ETeam_ID::MONSTER))
	{
		if (OtherTeamId == GetGenericTeamId())
		{
			// 아군인 경우
			return ETeamAttitude::Friendly;
		}
		else
		{
			// 다른 몬스터인 경우
			return ETeamAttitude::Neutral;
		}
	}
	else
	{
		return Result;	
	}
}

FGenericTeamId AMJAIControllerBaseTG::GetGenericTeamId() const
{
	return TeamId;
}
