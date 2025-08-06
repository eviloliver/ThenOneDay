// ThenOneDayStudio


#include "TG/UI/MJDungeonNodeWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/GameMode/MJGameModeDungeon.h"
#include "TG/SubSystem/MJDungeonGenerationSubSystem.h"
#include "TG/SubSystem/MJSaveGameSubsystem.h"

void UMJDungeonNodeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UMJDungeonNodeWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	UMJDungeonGenerationSubSystem* DGSubSystem = GetGameInstance()->GetSubsystem<UMJDungeonGenerationSubSystem>();
	
	if (DGSubSystem)
	{
		const FMJDungeonGraph* DungeonGraph = DGSubSystem->GetDungeonGraph();

		uint8 NodeNumber;
		EMJNodeType NodeType = EMJNodeType::Battle;
		FMJDungeonNode Node;
		FString MapName;
		
		if (DungeonGraph)
		{
			NodeNumber = UKismetStringLibrary::Conv_StringToInt(NodeNum->GetText().ToString());
			NodeType = DungeonGraph->Nodes[NodeNumber].NodeType;
			Node = DungeonGraph->Nodes[NodeNumber];
		}
	
		if (AMJGameModeDungeon* GMDungeon = Cast<AMJGameModeDungeon>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			if (GMDungeon)
			{
				uint8 CurrentPlayerMapNum = GetGameInstance<UMJGameInstanceTG>()->GetPlayerSessionDataRef().CurrentDungeonMapNum;

				if (true)//GetGameInstance()->GetSubsystem<UMJDungeonGenerationSubSystem>()->CheckHasRoute(CurrentPlayerMapNum, NodeNumber))
				{
					
					switch (NodeType)
					{
					case EMJNodeType::Battle:
						MapName = FString::Printf(TEXT("Dungeon_Chunk_Battle0%d"), Node.AssignedMapID);
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
					
					
					
					GMDungeon->TravelToMapByNode(MapName,UKismetStringLibrary::Conv_StringToInt(NodeNum->GetText().ToString()));

					FInputModeGameAndUI InputMode;
					InputMode.SetHideCursorDuringCapture(false);
					UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(InputMode);
					
					return FReply::Handled();
				}
			}
		}
	}
	return FReply::Unhandled();
}

