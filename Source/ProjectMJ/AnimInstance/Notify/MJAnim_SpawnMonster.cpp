// ThenOneDayStudio


#include "AnimInstance/Notify/MJAnim_SpawnMonster.h"

#include "ProjectMJ.h"
#include "MJ/Character/MJBossMonsterCharacter.h"
#include "TG/MJGameInstance.h"
#include "Character/Component/MJEnemySkillComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


void UMJAnim_SpawnMonster::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!SpawnMonster)
	{
		return;
	}

	if (SpawnCount <= 0)
	{
		return;
	}

	AMJBossMonsterCharacter* Owner = Cast<AMJBossMonsterCharacter>(MeshComp->GetOwner());
	if (!Owner)
	{
		return;
	}
	if (!SpawnLocation.IsEmpty())
	{
		SpawnLocation.Empty();
	}

	int32 LimitSearch = SpawnCount * 10;
	
	float InnerRadius = Owner->GetCapsuleComponent()->GetScaledCapsuleRadius();
	float ExcludeHalfAngle = FMath::DegreesToRadians(60.f);

	for (int32 i = 0; i < SpawnCount; i++)
	{
		bool SpawnCheck = false;
		FVector NewDistance;
		
		/*for (int Attempt = 0; Attempt < LimitSearch; Attempt++)
		{*/
		while (SpawnLocation.Num() <SpawnCount)
		{
			float Angle = FMath::FRandRange(0.f, 2 * PI);
			float Distance = FMath::Sqrt(FMath::FRandRange(InnerRadius * InnerRadius, OuterRadius * OuterRadius));

			float OffsetX = FMath::Cos(Angle) * Distance;
			float OffsetY = FMath::Sin(Angle) * Distance;

			NewDistance = FVector(Owner->GetActorLocation().X + OffsetX, Owner->GetActorLocation().Y + OffsetY, 0.f);

			FVector DirToCandidate = (NewDistance - Owner->GetActorLocation()).GetSafeNormal();
			float Dot = FVector::DotProduct(Owner->GetActorForwardVector(), DirToCandidate);
			if (FMath::Acos(Dot) < ExcludeHalfAngle)
			{
				continue;
			}

			bool bTooClose = false;
			for (const FVector& OldLocation : SpawnLocation)
			{
				if (FVector::Dist(OldLocation, NewDistance) < MinDistance)
				{
					bTooClose = true;
					break;
				}
			}
			if (!bTooClose)
			{

				SpawnCheck = true;
				break;
			}
			//}
		}
		if (SpawnCheck)
		{
			SpawnLocation.Add(NewDistance);
			GetWorld()->SpawnActor<APawn>(SpawnMonster, NewDistance, FRotator::ZeroRotator); 
		}
	}

	DrawDebugCircle(GetWorld(), Owner->GetActorLocation(), InnerRadius, 16, FColor::White, false, 0.2f, 0, 0, FVector::RightVector, FVector::ForwardVector, false);
	DrawDebugCircle(GetWorld(), Owner->GetActorLocation(), OuterRadius, 16, FColor::Black,false, 0.2f, 0, 0, FVector::RightVector, FVector::ForwardVector, false);

}
