// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/MJMonsterAIControllerBase.h"
#include "AIPerceptionInfo.h"
#include "ProjectMJ.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Hearing.h"

AMJMonsterAIControllerBase::AMJMonsterAIControllerBase()
{
	/*
	 * Minjin
	 * How To: AIPerception
	 * 감지할 감각을 AIPerception에 등록->에디터에서 진행
	 * 캐릭터(감지대상)에도 PerceptionStimuli Source 부착 필요!->감지되는 감각을 명시적으로 표시하기 위한 과정인듯
	 */
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	
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
	if (nullptr == ControlledPawn)
	{
		UE_LOG(LogTemp, Log, TEXT("AIController: ControlledPawn is null."))
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

	UAIPerceptionSystem::GetCurrent(GetWorld())->UpdateListener(*AIPerceptionComponent);
}

void AMJMonsterAIControllerBase::RunAI()
{
	/*
	 * Minjin
	 * How To: BehaviorTree 작동-RunBehaviorTree
	 * 블랙보드 초기화, StartTree
	 * StartLogic()에서 DefaultBehaviorTreeAsset(에디터에서 설정)을 시작에셋으로 설정해준다.
	 */
	BehaviorTreeComponent->StartLogic();
	RunBehaviorTree(BehaviorTreeComponent->GetCurrentTree());;
}

void AMJMonsterAIControllerBase::StopAI()
{
	/*
	 * TODO
	 * Character가 죽을 때 호출해야 됨?
	 */
	BehaviorTreeComponent->StopTree();
}

void AMJMonsterAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	 RunAI();
}

void AMJMonsterAIControllerBase::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor == nullptr)
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
		 * How to: 감지된 감각을 각각 처리->오버라이드해서 사용
		 */
		// Minjin: 감지한 첫 순간
		if(Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			HandleSight_Detected(Actor, Stimulus);
		}
		else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Damage>())
		{
			HandleDamage_Detected(Actor, Stimulus);
		}
		else if(Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
		{
			HandleHearing_Detected(Actor, Stimulus);
		}
	}
	else
	{
		// Minjin: 감지 실패한 첫 순간
		if(Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			HandleSight_Lost(Actor, Stimulus);
		}
		else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Damage>())
		{
			HandleDamage_Lost(Actor, Stimulus);
		}
		else if(Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
		{
			HandleHearing_Lost(Actor, Stimulus);
		}
	}		
}

ETeamAttitude::Type AMJMonsterAIControllerBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	ETeamAttitude::Type Result = Super::GetTeamAttitudeTowards(Other);

	/*
	 * Minjin
	 * How TO: TeamId 비교해서 플레이어, NPC, 몬스터로 나눈다.-에디터에서 ID를 설정(캐릭터)
	 */

	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (OtherPawn == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	const IGenericTeamAgentInterface* OtherCharacter = Cast<IGenericTeamAgentInterface> (&Other);
	if (OtherCharacter == nullptr)
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
	Blackboard->SetValueAsObject("Target", Actor);
	UE_LOG(LogMJ, Log, TEXT("시야로 감지"));
	Blackboard->SetValueAsBool("IsTargetVisible", true);
}

void AMJMonsterAIControllerBase::HandleDamage_Detected(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogMJ, Log, TEXT("데미지로 감지"));
	
	Blackboard->SetValueAsVector("DamagePos", Stimulus.StimulusLocation);		
}

void AMJMonsterAIControllerBase::HandleHearing_Detected(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogMJ, Log, TEXT("소리로 감지"));
	
	Blackboard->SetValueAsVector("HearingPos", Stimulus.StimulusLocation);
}

void AMJMonsterAIControllerBase::HandleHearing_Lost(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogMJ, Log, TEXT("소리감지 해제"));
	
	Blackboard->ClearValue("HearingPos");
}

void AMJMonsterAIControllerBase::HandleSight_Lost(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Log, TEXT("시야 감지 해제"));
	Blackboard->SetValueAsVector("LastKnownPos", Stimulus.StimulusLocation);
	Blackboard->ClearValue("IsTargetVisible");
}

void AMJMonsterAIControllerBase::HandleDamage_Lost(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogMJ, Log, TEXT("데미지 감지 해제"));
	
	Blackboard->ClearValue("DamagePos");
}
