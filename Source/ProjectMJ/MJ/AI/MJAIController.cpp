// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/MJAIController.h"

#include "AIPerceptionInfo.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/MJPlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AMJAIController::AMJAIController()
{
	/*
	 * TODO
	 * AIPerception 하드코딩 변경하기
	 */
	// AIPerception
	// Sense-Sight
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("AISenseConfig_Sight");
	AISenseConfig_Sight->SightRadius = 1000.0f;
	AISenseConfig_Sight->LoseSightRadius = 1500.0f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 60.0f;

	// 적, 중립, 아군 감지 여부 -> 어떻게 판단? TeamId를 부여한다.=>GetTeamAttitudeTowards에서 판단
	// 우선 적(플레이어)만 감지하게 함.
	// 만약 대상별로 다르게 행동을하는게 필요하다면 TargetPerceptionUpdated에 추가 구현 필요할 것
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;

	// AiPerception
	// 설정-> 캐릭터에도 PerceptionStimuli Source 부착 필요!
	// PerceptionComp를 Create로 가져와야 Crash 안 남(AIController에 있는 AIPerceptionCompopnent는 포인터만 선언한 것)
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMJAIController::TargetPerceptionUpdated);

	// TeamId
	TeamId = FGenericTeamId(static_cast<uint8>(ETeam_ID::Monster));
	
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_MJMonster.BB_MJMonster'"));
	if (nullptr!=BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_MJMonster.BT_MJMonster'"));
	if (nullptr!= BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AMJAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		// 시작 위치 값 설정
		Blackboard->SetValueAsVector("HomePos", GetPawn()->GetActorLocation());
		
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AMJAIController::StopAI()
{
	/*
	 * TODO
	 * Character가 죽을 때 호출해야 됨
	 */
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AMJAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void AMJAIController::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (nullptr==Actor)
	{
		return;
	}

	// Stimulus.Type.Name으로 어떤 감각인지 얻을 수 있다. ex. Stimulus.Type.Name == "Sight" ->시야
	// Stimulus.StimulusLocation으로 위치를 받아올 수 있다.
	
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTemp, Log, TEXT("Detect"));
		Blackboard->SetValueAsObject("Target", Actor);
		Blackboard->SetValueAsBool("IsTargetVisible", true);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UnDetect"));
		Blackboard->ClearValue("IsTargetVisible");
	}		
}

ETeamAttitude::Type AMJAIController::GetTeamAttitudeTowards(const AActor& Other) const
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
	if (OtherTeamId == 0)
	{
		// 플레이어인 경우
		return ETeamAttitude::Hostile;
	}
	else if ((OtherTeamId>=static_cast<uint8>(ETeam_ID::NPC))&&
		(OtherTeamId<static_cast<uint8>(ETeam_ID::Monster)))
	{
		// NPC인 경우
		return ETeamAttitude::Neutral;
	}
	else if (OtherTeamId>=static_cast<uint8>(ETeam_ID::Monster))
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
