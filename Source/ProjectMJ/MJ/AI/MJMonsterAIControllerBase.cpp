// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/MJMonsterAIControllerBase.h"
#include "AIPerceptionInfo.h"
#include "ProjectMJ.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "mj/Interface/MJCharacterAIInterface.h"

AMJMonsterAIControllerBase::AMJMonsterAIControllerBase()
{
	/*
	 * How To: AIPerception
	 * 감지할 감각을 AIPerception에 등록->BeginPlay()에서 한다.
	 * 감지할 감각(Sight), AIPerception 생성은 생성자에서 해야 한다.
	 * 캐릭터(감지대상)에도 PerceptionStimuli Source 부착 필요!
	 */
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("AISenseConfig_Sight");
	
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(
		this, &AMJMonsterAIControllerBase::TargetPerceptionUpdated);

}

void AMJMonsterAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	APawn* ControlledPawn = GetPawn();
	if (nullptr == ControlledPawn)
	{
		UE_LOG(LogTemp, Log, TEXT("AIController: ControlledPawn is null."))
	}
	// interface를 통해 Sight에 관련된 데이터를 받아온다.
	IMJCharacterAIInterface* AIPawn = Cast<IMJCharacterAIInterface>(ControlledPawn);
	if (nullptr == AIPawn)
	{
		UE_LOG(LogTemp, Log, TEXT("AIController: AIPawn is null."));

		AISenseConfig_Sight->SightRadius = 800.0f;
		AISenseConfig_Sight->LoseSightRadius = 1000.0f;
		AISenseConfig_Sight->PeripheralVisionAngleDegrees = 60.0f;
	}
	else
	{
		AISenseConfig_Sight->SightRadius = AIPawn->GetAISight_SightRadius();
		AISenseConfig_Sight->LoseSightRadius = AIPawn->GetAISight_LoseSightRadius();
		AISenseConfig_Sight->PeripheralVisionAngleDegrees = AIPawn->GetAISight_PeripheralVisionAngleDegrees();
	}
	
	/*
	 * How To: 적, 중립, 아군 감지 여부
	 * TeamId로 판단=>GetTeamAttitudeTowards에서 판단
	 * 적(플레이어)만 감지하는 상태.
	 */
	/*
	 * TODO
	 * 자손 클래스에서 업데이트 불가능..., 플레이해야 반영된게 보인다(당연함. BeginPlay임)
	 * 다른 방법 모색중...
	 */
	DetectionByAffiliation = AISenseConfig_Sight->DetectionByAffiliation;
	DetectionByAffiliation.bDetectEnemies = true;
	DetectionByAffiliation.bDetectNeutrals = false;
	DetectionByAffiliation.bDetectFriendlies = false;
	
	// 감각 등록
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	
	/*
	 * How to: AIController의 TeamId 설정
	 * AIController를 이용하고 있는 폰의 TeamId를 가져온다.
	 */
	if (nullptr== ControlledPawn)
	{
		TeamId = 255;
	}
	else
	{
		IGenericTeamAgentInterface* AITeamPawn = Cast<IGenericTeamAgentInterface>(ControlledPawn);
		if (nullptr == AITeamPawn)
		{
			TeamId = 255;
		}
		else
		{
			TeamId = AITeamPawn->GetGenericTeamId();
		}
	}
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
