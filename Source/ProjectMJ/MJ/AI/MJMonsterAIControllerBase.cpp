// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/MJMonsterAIControllerBase.h"
#include "AIPerceptionInfo.h"
#include "ProjectMJ.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "mj/Interface/MJCharacterAIInterface.h"

AMJMonsterAIControllerBase::AMJMonsterAIControllerBase()
{
	/*
	 * How To: AIPerception
	 * 감지할 감각을 AIPerception에 등록->BeginPlay()에서 한다.
	 * 감지할 감각(Sight), AIPerception 생성은 생성자에서 해야 한다.
	 * 캐릭터(감지대상)에도 PerceptionStimuli Source 부착 필요!
	 */
	// AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("AISenseConfig_Sight");
	// AISenseConfig_Damage = CreateDefaultSubobject<UAISenseConfig_Damage>("AISenseConfig_Damage");
	
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

	//UAIPerceptionSystem::GetCurrent(GetWorld())->UpdateListener(*AIPerceptionComponent);
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
	
	// Minjin: Stimulus.Type으로 감각가져오기 - ex. Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>()
	// Minjin: Stimulus.Type.Name은 FName인데 이름이 Default__AISense_Sight 이런 식임
	// Stimulus.StimulusLocation으로 위치를 받아올 수 있다.
	
	if (Stimulus.WasSuccessfullySensed())
	{
		/*
		 * Minjin
		 * TODO
		 * 모든 감각에 대한 함수 만들고 자식에서 오버라이드해서 구현하기(현재는 시야, 데미지만 추가)
		 */
		Blackboard->SetValueAsObject("Target", Actor);
		
		if(Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			HandleSight_Detected(Actor, Stimulus);
		}
		else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Damage>())
		{
			HandleDamage_Detected(Actor, Stimulus);
		}
	}
	else
	{
		if(Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			HandleSight_Lost(Actor, Stimulus);
		}
		else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Damage>())
		{
			HandleDamage_Lost(Actor, Stimulus);
		}
		
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

void AMJMonsterAIControllerBase::HandleSight_Detected(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogMJ, Log, TEXT("시야로 감지"));
	Blackboard->SetValueAsBool("IsTargetVisible", true);
}

void AMJMonsterAIControllerBase::HandleDamage_Detected(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogMJ, Log, TEXT("데미지로 감지"));
	GetBlackboardComponent()->SetValueAsVector("DamagePos", Stimulus.StimulusLocation);
}

void AMJMonsterAIControllerBase::HandleSight_Lost(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Log, TEXT("UnDetect"));
	GetBlackboardComponent()->SetValueAsVector("LastKnownPos", Stimulus.StimulusLocation);
	Blackboard->ClearValue("IsTargetVisible");
}

void AMJMonsterAIControllerBase::HandleDamage_Lost(AActor* Actor, FAIStimulus Stimulus)
{
}
