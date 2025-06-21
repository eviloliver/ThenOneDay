// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/MJMonsterAIControllerBase.h"
#include "AIPerceptionInfo.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AMJMonsterAIControllerBase::AMJMonsterAIControllerBase()
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

	/*
	 * How To: 적, 중립, 아군 감지 여부
	 * TeamId를 부여한다.=>GetTeamAttitudeTowards에서 판단
	 * 우선 적(플레이어)만 감지하게 함.
	 * // 만약 대상별로 다르게 행동을하는게 필요하다면 TargetPerceptionUpdated에 추가 구현 필요할 것
	 */
	/*
	 * TODO
	 * 자손에서 Detect 설정
	 */
	// AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	// AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	// AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;

	// 에디터에서 설정한 거 확인용 (더 나은 방법이 있다면 알려주세요)
	/*
	 * TODO
	 * 자손 클래스에서 업데이트 불가능... 고치기 => 함수로 빼기?
	 */
	DetectionByAffiliation = AISenseConfig_Sight->DetectionByAffiliation;
	DetectionByAffiliation.bDetectEnemies = true;
	DetectionByAffiliation.bDetectNeutrals = false;
	DetectionByAffiliation.bDetectFriendlies = false;
	
	/*
	 * How To: AiPerception
	 * 감지할 감각 등록
	 * 캐릭터(감지대상)에도 PerceptionStimuli Source 부착 필요!
	 */
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(
		this, &AMJMonsterAIControllerBase::TargetPerceptionUpdated);
}

void AMJMonsterAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	 * How to: AIController의 TeamId 설정
	 * AIController를 이용하고 있는 폰의 TeamId를 가져온다.
	 */
	APawn* ControlledPawn = GetPawn();
	if (nullptr== ControlledPawn)
	{
		TeamId = 255;
	}
	IGenericTeamAgentInterface* AIPawn = Cast<IGenericTeamAgentInterface>(ControlledPawn);
	if (nullptr == AIPawn)
	{
		TeamId = 255;
	}

	TeamId = AIPawn->GetGenericTeamId();
}

void AMJMonsterAIControllerBase::RunAI()
{
	UBlackboardData* BBAsset = BehaviorTree->GetBlackboardAsset();
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		// 시작 위치 값 설정
		Blackboard->SetValueAsVector("HomePos", GetPawn()->GetActorLocation());
		
		bool RunResult = RunBehaviorTree(BehaviorTree);
		ensure(RunResult);
	}
}

void AMJMonsterAIControllerBase::StopAI()
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

void AMJMonsterAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void AMJMonsterAIControllerBase::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
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

ETeamAttitude::Type AMJMonsterAIControllerBase::GetTeamAttitudeTowards(const AActor& Other) const
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
