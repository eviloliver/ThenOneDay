// ThenOneDayStudio

#include "TG/Actor/MJPortalToDungeon.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameMode/MJGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/GameMode/MJGameModeTown.h"
#include "TG/SubSystem/MJDungeonGenerationSubSystem.h"
#include "TG/SubSystem/MJSaveGameSubsystem.h"

AMJPortalToDungeon::AMJPortalToDungeon()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(StaticMesh);
}

void AMJPortalToDungeon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AMJPortalToDungeon::GotoDungeon);
}

void AMJPortalToDungeon::GotoDungeon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UMJDungeonGenerationSubSystem* SubSystem = GetGameInstance()->GetSubsystem<UMJDungeonGenerationSubSystem>();
	if (SubSystem)
	{
		SubSystem->GenerateDungeonGraph();
	}

	// UAudioComponent* AudioComp = UGameplayStatics::SpawnSound2D(GetWorld(),CollisionSFX);
	//
	// AudioComp->OnAudioFinished.AddDynamic(this, &AMJPortalToDungeon::OnAudioFinish);
	OnAudioFinish();
}

void AMJPortalToDungeon::OnAudioFinish()
{
	UMJDungeonGenerationSubSystem* SubSystem = GetGameInstance()->GetSubsystem<UMJDungeonGenerationSubSystem>();
	AMJGameModeTown* GMTown = Cast<AMJGameModeTown>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GMTown && SubSystem)
	{
		uint8 NodeId = SubSystem->GetDungeonGraph()->Nodes[GetGameInstance<UMJGameInstanceTG>()->GetPlayerSessionDataRef().CurrentDungeonMapNum].AssignedMapID;
		EMJNodeType NodeType = SubSystem->GetDungeonGraph()->Nodes[GetGameInstance<UMJGameInstanceTG>()->GetPlayerSessionDataRef().CurrentDungeonMapNum].NodeType;

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


