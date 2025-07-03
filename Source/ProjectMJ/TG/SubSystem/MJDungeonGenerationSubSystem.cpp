// Fill out your copyright notice in the Description page of Project Settings.


#include "MJDungeonGenerationSubSystem.h"
#include <functional>
#include "ProjectMJ.h"
#include "TG/MJGameInstanceTG.h"


UMJDungeonGenerationSubSystem::UMJDungeonGenerationSubSystem()
{
	MaxNodeNum = 10;
}

void UMJDungeonGenerationSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GenerateDungeonGraph();
}

bool UMJDungeonGenerationSubSystem::GenerateDungeonGraph()
{
	UMJGameInstanceTG* MJGI = Cast<UMJGameInstanceTG>(GetGameInstance());

	check(MJGI);
	
	FVector2D StartPoint;
	FVector2D EndPoint;

	FVector2D ControlPoint;
	uint8 CurrentNotAssignedNodeNum = 0;
	
	FVector2D ViewportSize = FVector2D(1920.f,1080.f);

	// Sets Bezier Curve Points (for now, just one curve)
	StartPoint = FVector2D(ViewportSize.X / 4,ViewportSize.Y * 0.5);
	EndPoint = FVector2D(ViewportSize.X - ViewportSize.X / 4,ViewportSize.Y * 0.5);
	ControlPoint = FVector2D(ViewportSize.X/2,ViewportSize.Y * 0.05);

	while (CurrentNotAssignedNodeNum < MaxNodeNum)
	{
		// divide curve and make nodes
		float t = static_cast<float>(CurrentNotAssignedNodeNum) / (MaxNodeNum - 1);
		
		FVector2D BezierPoint = GetQuadBezier(t, StartPoint, EndPoint, ControlPoint);
		DungeonGraph.BezierPoints.Add(BezierPoint);
	
		float OffsetPivot = 200.f;
		
		FVector2D RandomOffset = FVector2D(FMath::RandRange(-OffsetPivot,OffsetPivot), FMath::RandRange(-OffsetPivot,OffsetPivot));
		FVector2D BasePosition = BezierPoint;
		FVector2D CandidatePoint = BasePosition + RandomOffset;
		
		// When Node is outside of Viewpoert, re-generates node.
		if (CandidatePoint.X < 0.f || CandidatePoint.X > ViewportSize.X ||
			CandidatePoint.Y < 0.f || CandidatePoint.Y > ViewportSize.Y)
		{
			continue;
		}
		
		// When Created Node Position is too close, re-generates node.
		uint8 TooCloseNodesNum = 0;
		for (auto& iter : DungeonGraph.Nodes)
		{
			if (FVector2D::Distance(CandidatePoint, iter.UICoordinate) < OffsetPivot )
			{
				TooCloseNodesNum++;
			}
		}
		
		if (TooCloseNodesNum > 0)
		{
			continue;
		}

		// Determine Map`s Type
		float Prob = FMath::RandRange(0.0f,100.f);
		
		// First, Check is there any boss room in DungeonGraph
		if (CurrentNotAssignedNodeNum == MaxNodeNum - 1 && DungeonGraph.BossNodeID == -1)
		{
			// Boss
			
			FDungeonNode NewNode = MakeNewNode(CurrentNotAssignedNodeNum,0,ENodeType::Boss, EAISpawnType::Static, CandidatePoint);
			DungeonGraph.Nodes.Add(NewNode);
			DungeonGraph.BossNodeID = CurrentNotAssignedNodeNum;

			MJGI->GetDungeonSessionDataRef().Add(FMJDungeonSessionData(EMJDungeonContext::InActive, CurrentNotAssignedNodeNum, EAISpawnType::Static, FString(TEXT("Boss"))));
	
			CurrentNotAssignedNodeNum++;
			
		}
		else if (Prob > 0.0f && Prob < 80.f)
		{	
			// Battle 1~5 Map Assign 
			float RandNum = FMath::RandRange(1,5);

			EAISpawnType AISpawnType = EAISpawnType::Static;
			float RandNumAISpawn = FMath::RandRange(1,4);

			if (RandNumAISpawn == 1)
			{
				AISpawnType = EAISpawnType::Wave;
			}
			
			FDungeonNode NewNode = MakeNewNode(CurrentNotAssignedNodeNum,RandNum,ENodeType::Battle, AISpawnType, CandidatePoint);
			DungeonGraph.Nodes.Add(NewNode);

			MJGI->GetDungeonSessionDataRef().Add(FMJDungeonSessionData(EMJDungeonContext::InActive, CurrentNotAssignedNodeNum, AISpawnType, FString(TEXT("Battle"))));
			
			CurrentNotAssignedNodeNum++;
		}
		else if (Prob >= 80.f && Prob < 90.f)
		{
			// Reward
			FDungeonNode NewNode = MakeNewNode(CurrentNotAssignedNodeNum,0,ENodeType::Reward, EAISpawnType::Static, CandidatePoint);
			DungeonGraph.Nodes.Add(NewNode);

			
			MJGI->GetDungeonSessionDataRef().Add(FMJDungeonSessionData(EMJDungeonContext::InActive, CurrentNotAssignedNodeNum, EAISpawnType::Static, FString(TEXT("Reward"))));
	
			CurrentNotAssignedNodeNum++;
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
				continue;
			}
			
			FDungeonNode NewNode = MakeNewNode(CurrentNotAssignedNodeNum,0,ENodeType::Boss, EAISpawnType::Static, CandidatePoint);
			DungeonGraph.Nodes.Add(NewNode);
			DungeonGraph.BossNodeID = CurrentNotAssignedNodeNum;

			MJGI->GetDungeonSessionDataRef().Add(FMJDungeonSessionData(EMJDungeonContext::InActive, CurrentNotAssignedNodeNum, EAISpawnType::Static,  FString(TEXT("Boss"))));
	
			CurrentNotAssignedNodeNum++;
		}
	} 
	
	// @fixme : maybe cause infinite loop ?
	// temporaily, start at random node
	
	// uint8 tmp;
	// while (true)
	// {
	// 	tmp = FMath::RandRange(0,CurrentNotAssignedNodeNum - 1);
	//
	// 	if (DungeonGraph.Nodes[tmp].NodeType == ENodeType::Battle)
	// 	{
	// 		DungeonGraph.StartNodeID = tmp;
	// 		SavedMapNodeNum = tmp;
	// 		break;
	// 	}
	// }

	// Choose most far node from BossNode
	float MaxDist = FLT_MIN;
	uint8 MaxDistNodeNum = -1;
	for (auto& iter : DungeonGraph.Nodes)
	{
		if (iter.NodeType  != ENodeType::Battle)
			continue;
		
		if (MaxDist < FVector2D::Distance(DungeonGraph.Nodes[iter.NodeID].UICoordinate, DungeonGraph.Nodes[DungeonGraph.BossNodeID].UICoordinate))
		{
			MaxDist = FVector2D::Distance(DungeonGraph.Nodes[iter.NodeID].UICoordinate, DungeonGraph.Nodes[DungeonGraph.BossNodeID].UICoordinate);
			MaxDistNodeNum = iter.NodeID;
			
		}
	}
	
	DungeonGraph.StartNodeID = MaxDistNodeNum;

	if (MJGI)
	{
		MJGI->GetPlayerSessionDataRef().CurrentDungeonMapNum = DungeonGraph.StartNodeID;
		
	}
	
#pragma region Debug
	
	// for (int i = 0 ; i < CurrentNotAssignedNodeNum ; i++)
	// {
	// 	MJ_LOG(LogTG, Warning, TEXT("Node Num = %d,  Node Assigned Num = %d, NodeType = %s"), DungeonGraph.Nodes[i].NodeID,DungeonGraph.Nodes[i].AssignedMapID, *FDungeonNode::NodeTypeToString(DungeonGraph.Nodes[i].NodeType));
	// }
	//
	//
	// for (int i = 0 ; i < CurrentNotAssignedNodeNum ; i++)
	// {
	// 	const FDungeonNode& Node = DungeonGraph.Nodes[i];
	// 	bool bOutOfBounds =
	// 		Node.UICoordinate.X < 0.f || Node.UICoordinate.X > ViewportSize.X ||
	// 		Node.UICoordinate.Y < 0.f || Node.UICoordinate.Y > ViewportSize.Y;
	//
	// 	if (bOutOfBounds)
	// 	{
	// 		MJ_LOG(LogTG, Error, TEXT(" OUT OF BOUNDS → Node ID: %d | Pos: X=%.1f, Y=%.1f (Viewport: %.1f x %.1f)"),
	// 			Node.NodeID,
	// 			Node.UICoordinate.X,
	// 			Node.UICoordinate.Y,
	// 			ViewportSize.X,
	// 			ViewportSize.Y);
	// 	}
	// 	else
	// 	{
	// 		MJ_LOG(LogTG, Log, TEXT("Node ID: %d | Pos: X=%.1f, Y=%.1f"),
	// 			Node.NodeID,
	// 			Node.UICoordinate.X,
	// 			Node.UICoordinate.Y);
	// 	}
	// }
	// for (int i = 0 ; i < CurrentNotAssignedNodeNum ; i++)
	// {
	// 	const FDungeonNode& Node = DungeonGraph.Nodes[i];
	//
	// 	MJ_LOG(LogTG, Warning, TEXT("Node ID: %d | Type: %s | Pos: X=%.1f, Y=%.1f"),
	// 		Node.NodeID,
	// 		*FDungeonNode::NodeTypeToString(Node.NodeType),
	// 		Node.UICoordinate.X,
	// 		Node.UICoordinate.Y);
	// }
#pragma endregion 
	
	ConnectNodesByMST(FVector2D::Distance(FVector2D(0.0f,0.0f), ViewportSize));
	
	ConnectNodesByDistance(400.f,4);
	
	return true;
}

FDungeonNode UMJDungeonGenerationSubSystem::MakeNewNode(uint8 NodeNum, uint8 AssignedMapID, ENodeType NodeType,EAISpawnType AISpawnType, FVector2D UICoordinate)
{
	FDungeonNode NewNode;

	NewNode.NodeID = NodeNum;
	NewNode.AssignedMapID = AssignedMapID;
	NewNode.NodeType = NodeType;
	NewNode.AISpawnType = AISpawnType;
	NewNode.UICoordinate = UICoordinate;
	
	return NewNode;
}

void UMJDungeonGenerationSubSystem::ConnectNodesByDistance(float MaxDistance, int MaxEdgePerNode)
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
			
			float DistanceBetweenNodes = FVector2D::Distance(CurrentNode.UICoordinate, IterNode.UICoordinate);
			
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
				CurrentNode.ConnectedNodeIDs.Num() < MaxEdgePerNode)
				//&& DungeonGraph.Nodes[TargetIndex].ConnectedNodeIDs.Num() < FMath::RandRange(2,MaxEdgePerNode))
			{
				CurrentNode.ConnectedNodeIDs.Add(TargetIndex);
				DungeonGraph.Nodes[TargetIndex].ConnectedNodeIDs.Add(i);
			}
		}
	}

	// for debug
	// for (const FDungeonNode& Node : DungeonGraph.Nodes)
	// {
	// 	FString ConnectedStr;
	// 	for (int32 ID : Node.ConnectedNodeIDs)
	// 	{
	// 		ConnectedStr += FString::Printf(TEXT("%d "), ID);
	// 	}
	//
	// 	MJ_LOG(LogTG, Warning, TEXT("Node %d (%s) → [%s]"),
	// 		Node.NodeID,
	// 		*FDungeonNode::NodeTypeToString(Node.NodeType),
	// 		*ConnectedStr);
	// }
	
}

void UMJDungeonGenerationSubSystem::ConnectNodesByMST(float MaxDistance)
{
	const uint8 NodeCount = DungeonGraph.Nodes.Num();

	if ( NodeCount <= 1 ) return;
	
	TArray<TTuple<uint8, uint8, float>> AllCandidateEdges;
	for (int i = 0 ; i< NodeCount ; i++)
	{
		for (int j = 0 ; j < NodeCount ; j++)
		{
			if (i == j) continue;

			float Distance = FVector2D::Distance(DungeonGraph.Nodes[i].UICoordinate,DungeonGraph.Nodes[j].UICoordinate);
	
			AllCandidateEdges.Add(MakeTuple(i,j,Distance));
		}
	}
	
	AllCandidateEdges.Sort([](const TTuple<uint8, uint8, float>& A, const TTuple<uint8, uint8, float>& B)
	{
		return A.Get<2>() < B.Get<2>();
	});
	
	TArray<int16> Parent;
	Parent.Init(-1,NodeCount);

	std::function<uint8(uint8)> Find = [&Parent, &Find](uint8 Node) -> uint8
	{
		if (Parent[Node] < 0 ) return Node;
		return Parent[Node] = Find(Parent[Node]);
	};

	std::function<bool(uint8, uint8)> Union = [&Parent, &Find](uint8 A, uint8 B) -> bool
	{
		uint8 RootA = Find(A);
		uint8 RootB = Find(B);

		if (RootA == RootB) return false;
		
		Parent[RootB] = RootA;
		return true;
	};
	
	for (const auto& iter : AllCandidateEdges)
	{
		uint8 NodeA = iter.Get<0>();
		uint8 NodeB = iter.Get<1>();

		if (Union(NodeA, NodeB))
		{
			DungeonGraph.Nodes[NodeA].ConnectedNodeIDs.Add(NodeB);
			DungeonGraph.Nodes[NodeB].ConnectedNodeIDs.Add(NodeA);
		}
	}
}

bool UMJDungeonGenerationSubSystem::CheckHasRoute(uint8 CurrentNodeNum, uint8 DestNodeNum)
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

FVector2D UMJDungeonGenerationSubSystem::GetCubicBezier(float t, const FVector2D Point)
{
	return FVector2D(0,0);
}

FVector2D UMJDungeonGenerationSubSystem::GetQuadBezier(float t, const FVector2D StartPoint, const FVector2D EndPoint,
	const FVector2D ControlPoint)
{
	return pow((1-t),2) * StartPoint + 2 * (1-t) * t * ControlPoint + pow(t,2) * EndPoint; 
}

uint8 UMJDungeonGenerationSubSystem::GetMaxNodeNum() const
{
	return MaxNodeNum;
}

void UMJDungeonGenerationSubSystem::SetMaxNodeNum(uint8 NewMaxNodeNum)
{
	MaxNodeNum = NewMaxNodeNum;
}