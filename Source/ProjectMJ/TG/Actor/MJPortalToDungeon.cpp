// ThenOneDayStudio

#include "TG/Actor/MJPortalToDungeon.h"

#include "GameMode/MJGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TG/MJGameInstance.h"
#include "TG/GameMode/MJGameModeTown.h"
#include "TG/SubSystem/MJDungeonGenerationSubSystem.h"
#include "TG/SubSystem/MJSaveGameSubsystem.h"

AMJPortalToDungeon::AMJPortalToDungeon()
{
	// TG : Don`t change this for proper SpawnActor
	SetActorRelativeScale3D(FVector(0.38f,0.2f,0.38f));
}


void AMJPortalToDungeon::Execute()
{
	Super::Execute();
	
	UMJDungeonGenerationSubSystem* SubSystem = GetGameInstance()->GetSubsystem<UMJDungeonGenerationSubSystem>();
	if (SubSystem)
	{
		SubSystem->GenerateDungeonGraph();
	}
	
	AMJGameModeTown* GMTown = Cast<AMJGameModeTown>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GMTown && SubSystem)
	{
		uint8 NodeId = SubSystem->GetDungeonGraph()->Nodes[GetGameInstance<UMJGameInstance>()->GetPlayerSessionDataRef().CurrentDungeonMapNum].AssignedMapID;
		EMJNodeType NodeType = SubSystem->GetDungeonGraph()->Nodes[GetGameInstance<UMJGameInstance>()->GetPlayerSessionDataRef().CurrentDungeonMapNum].NodeType;

		FString MapName;
		
		switch (NodeType)
		{
		case EMJNodeType::Battle:
			MapName = FString::Printf(TEXT("Dungeon_Chunk_Battle0%d"),NodeId);
			break;
						
		case EMJNodeType::Boss:
			MapName = TEXT("Dungeon_Chunk_Boss");
			break;
		case EMJNodeType::Reward:
			MapName = TEXT("Dungeon_Chunk_Reward");
			break;
		}
		
		// GameSaveTiming

		GetGameInstance()->GetSubsystem<UMJSaveGameSubsystem>()->SaveGameToCurrentSlotNum();
					
		GMTown->TravelToMapByNode(MapName, NodeId);
		
		
	}
}

void AMJPortalToDungeon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	// TG : Don`t change this for proper SpawnActor
	SetActorRelativeScale3D(FVector(0.38f,0.2f,0.38f));
}


void AMJPortalToDungeon::BeginPlay()
{
	Super::BeginPlay();
}