// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameInstanceTG.h"

#include "MJHttpDownloadManager.h"
#include "MJSaveGame.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/MJCharacterAttributeSet.h"
#include "Character/MJPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UMJGameInstanceTG::UMJGameInstanceTG()
{
	SavedDummyPos = FVector(0.0f,0.0f,0.0f);

	Visited.Init(false, sizeof(uint8));
	SavedMapNodeNum = -1;
}

void UMJGameInstanceTG::Init()
{
	Super::Init();

	GenerateDungeonGraph();
	
	// Google Sheet Load
	HttpDownloader = NewObject<UMJHttpDownloadManager>();
	HttpDownloader->FetchGoogleSheetData();
	
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		CreateSaveGame();
		MJ_LOG(LogTG,Log,TEXT("Create SaveGame File"));
	}

	
}


bool UMJGameInstanceTG::GenerateDungeonGraph()
{
	for (int i = 0 ; i < 10 ; i++)
	{
		const int32 Columns = 4;
		const float GridX = 300.f;
		const float GridY = 250.f;
		const float OffsetX = 40.f;
		const float OffsetY = 30.f;

		// 위치 설정
		int32 Row = i / Columns;
		int32 Col = i % Columns;
		FVector2D BasePosition = FVector2D(Col * GridX, Row * GridY);
		FVector2D RandomOffset = FVector2D(FMath::FRandRange(-OffsetX, OffsetX), FMath::FRandRange(-OffsetY, OffsetY));

		float Prob = FMath::RandRange(0.0f,100.f);
		
		// 보스 방 없을 시
		if (i == 9 && DungeonGraph.BossNodeID == -1)
		{
			// Boss
			
			FDungeonNode NewNode = MakeNewNode(i,0,ENodeType::Boss, BasePosition + RandomOffset);
			DungeonGraph.Nodes.Add(NewNode);
			DungeonGraph.BossNodeID = i;
						
			break;
		}
		
		if (Prob > 0.0f && Prob < 80.f)
		{	
			// Battle 1~5
			float RandNum = FMath::RandRange(1,5);
			
			FDungeonNode NewNode = MakeNewNode(i,RandNum,ENodeType::Battle, BasePosition + RandomOffset);
			DungeonGraph.Nodes.Add(NewNode);
		}
		else if (Prob >= 80.f && Prob < 90.f)
		{
			// Reward
			FDungeonNode NewNode = MakeNewNode(i,0,ENodeType::Reward, BasePosition + RandomOffset);
			DungeonGraph.Nodes.Add(NewNode);
			
		}
		else if (Prob >= 90.f && Prob < 100.f)
		{
			// Boss

			bool HasBossRoom = false;
			for (auto iter : DungeonGraph.Nodes)
			{
				if (iter.NodeType == ENodeType::Boss)
				{
					HasBossRoom = true;
					break;
				}
			}

			if (HasBossRoom)
			{
				i--;
				continue;
			}
			
			FDungeonNode NewNode = MakeNewNode(i,0,ENodeType::Boss, BasePosition + RandomOffset);
			DungeonGraph.Nodes.Add(NewNode);
			DungeonGraph.BossNodeID = i;
		}
	} 

	// @fixme : maybe cause infinite loop ?
	// temporaily, start at random node
	uint8 tmp;
	while (true)
	{
		tmp = FMath::RandRange(0,DungeonGraph.Nodes.Num());

		if (DungeonGraph.Nodes[tmp].NodeType == ENodeType::Battle)
		{
			DungeonGraph.StartNodeID = tmp;
			SavedMapNodeNum = tmp;
			break;
		}
	}
		
	
	for (int i = 0 ; i < 10 ; i++)
	{
		MJ_LOG(LogTG, Warning, TEXT("Node Num = %d,  Node Assigned Num = %d, NodeType = %s"), DungeonGraph.Nodes[i].NodeID,DungeonGraph.Nodes[i].AssignedMapID, *FDungeonNode::NodeTypeToString(DungeonGraph.Nodes[i].NodeType));
	}

	ConnectDungeonNodesByDistance(600.f,3);

	
	float MinX = FLT_MAX;
	float MinY = FLT_MAX;

	for (const FDungeonNode& Node : DungeonGraph.Nodes)
	{
		MinX = FMath::Min(MinX, Node.UICoordinate.X);
		MinY = FMath::Min(MinY, Node.UICoordinate.Y);
	}

	for (FDungeonNode& Node : DungeonGraph.Nodes)
	{
		Node.UICoordinate -= FVector2D(MinX, MinY);
	}
	
	return true;
}

FDungeonNode UMJGameInstanceTG::MakeNewNode(uint8 NodeNum, uint8 AssignedMapID, ENodeType NodeType,
	FVector2D UICoordinate)
{
	FDungeonNode BuffNode;

	BuffNode.NodeID = NodeNum;
	BuffNode.AssignedMapID = AssignedMapID;
	BuffNode.NodeType = NodeType;
	BuffNode.UICoordinate = UICoordinate;
	
	return BuffNode;
} 


void UMJGameInstanceTG::ConnectDungeonNodesByDistance(float MaxDistance, int MaxEdgePerNode)
{
	 const int32 NodeCount = DungeonGraph.Nodes.Num();

	for (int i = 0 ; i < NodeCount ; i++)
	{
		FDungeonNode& CurrentNode = DungeonGraph.Nodes[i];

		TArray<TPair<uint32, float>> CandidateNodes;

		for (int j = 0 ; j < NodeCount ; j++)
		{
			if (i == j) continue;

			FDungeonNode& IterNode = DungeonGraph.Nodes[j];
			
			float DistanceBetweenNodes = FVector2d::Distance(CurrentNode.UICoordinate, IterNode.UICoordinate);
			
			if (DistanceBetweenNodes <= MaxDistance)
			{
				CandidateNodes.Add(TPair<uint32, float>(j,DistanceBetweenNodes));
			}
		}

		CandidateNodes.Sort([](const TPair<uint32, float> A, const TPair<uint32,float> B)
		{
			return A.Value < B.Value;
		});

		for (int k = 0 ; k < CandidateNodes.Num() ; k++)
		{
			int32 TargetIndex = CandidateNodes[k].Key;

			// 양방향 연결 체크 후 추가
			if (!CurrentNode.ConnectedNodeIDs.Contains(TargetIndex) &&
				!DungeonGraph.Nodes[TargetIndex].ConnectedNodeIDs.Contains(i) &&
				CurrentNode.ConnectedNodeIDs.Num() < MaxEdgePerNode &&
				DungeonGraph.Nodes[TargetIndex].ConnectedNodeIDs.Num() < FMath::RandRange(1,MaxEdgePerNode))
			{
				CurrentNode.ConnectedNodeIDs.Add(TargetIndex);
				DungeonGraph.Nodes[TargetIndex].ConnectedNodeIDs.Add(i);
			}
		}
	}
	
	for (const FDungeonNode& Node : DungeonGraph.Nodes)
	{
		FString ConnectedStr;
		for (int32 ID : Node.ConnectedNodeIDs)
		{
			ConnectedStr += FString::Printf(TEXT("%d "), ID);
		}

		MJ_LOG(LogTG, Warning, TEXT("Node %d (%s) → [%s]"),
			Node.NodeID,
			*FDungeonNode::NodeTypeToString(Node.NodeType),
			*ConnectedStr);
	}
	
}

bool UMJGameInstanceTG::CheckHasRoute(uint8 CurrentNodeNum, uint8 DestNodeNum)
{

	for (auto& iter:DungeonGraph.Nodes[CurrentNodeNum].ConnectedNodeIDs)
	{
		if (iter == DestNodeNum)
		{
			return true;
		}
	}

	return false;
}

void UMJGameInstanceTG::DFS(uint8 Node)
{
	
}


void UMJGameInstanceTG::CreateSaveGame()
{
	SaveGameData = CastChecked<UMJSaveGame>(UGameplayStatics::CreateSaveGameObject(UMJSaveGame::StaticClass()));
	if (SaveGameData)
	{
		//SaveGameToSlot(nullptr);
	}
}

void UMJGameInstanceTG::LoadSaveGame(AMJPlayerCharacter* Player)
{
	if (!Player) return;
	
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		MJ_LOG(LogTG, Log, TEXT("No save found. Saving current character state as default."));

		SaveGameData = CastChecked<UMJSaveGame>(UGameplayStatics::CreateSaveGameObject(UMJSaveGame::StaticClass()));
		SaveGameToSlot(Player); // 현재 캐릭터의 기본값으로 저장
		return;
	}

	
	 SaveGameData = Cast<UMJSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (SaveGameData)
	 {
		if (Player)
	 	{
	 		UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(Player->GetAbilitySystemComponent());
	 		
	 		UMJCharacterAttributeSet* MJCAS = const_cast<UMJCharacterAttributeSet*>(MJASC->GetSet<UMJCharacterAttributeSet>());

	 		SaveGameData->GetAttributeSaveData().ApplyTo(MJASC);
	 		
	 		MJ_LOG(LogTG,Log,TEXT("loaded health : %f"), MJASC->GetNumericAttribute(UMJCharacterAttributeSet::GetHealthAttribute()));
	 	}
	 }
}

void UMJGameInstanceTG::SaveGameToSlot(AMJPlayerCharacter* Player)
{
	if (SaveGameData)
	{
		if (Player)
		{
			UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(Player->GetAbilitySystemComponent());
			UMJCharacterAttributeSet* MJCAS = const_cast<UMJCharacterAttributeSet*>(MJASC->GetSet<UMJCharacterAttributeSet>());

			SaveGameData->GetAttributeSaveData() = FCharacterAttributeSaveData::FromAttributeSet(MJCAS);
			
			MJ_LOG(LogTG,Log,TEXT("saved health : %f"), SaveGameData->GetAttributeSaveData().Health);
		}
		else
		{
			bool bSaved = false;
			MJ_LOG(LogTG, Log, TEXT("Character Info Save success: %s"), bSaved ? TEXT("true") : TEXT("false"));
		}
		
		bool bSaved = UGameplayStatics::SaveGameToSlot(SaveGameData, SaveSlotName, UserIndex);
		MJ_LOG(LogTG, Log, TEXT("Save success: %s"), bSaved ? TEXT("true") : TEXT("false"));
		
	}
}


FVector UMJGameInstanceTG::GetSavedDummyPos()
{
	return SavedDummyPos;
}

uint8 UMJGameInstanceTG::GetSavedMapNodeNum()
{
	return SavedMapNodeNum;
}

void UMJGameInstanceTG::SetSavedDummyPos(FVector Input)
{
	SavedDummyPos = Input;
}
void UMJGameInstanceTG::SetSavedMapNodeNum(uint8 Input)
{
	SavedMapNodeNum = Input;
}

UMJSaveGame* UMJGameInstanceTG::GetSaveGameData()
{
	return SaveGameData;
}