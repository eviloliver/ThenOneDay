// ThenOneDayStudio


#include "MJ/Drop/Notify_MJSpawnTargetProjectile.h"

#include "MJTargetingProjectileBase.h"
#include "ProjectMJ.h"
#include "Character/MJPlayerCharacter.h"
#include "MJ/Character/MJMonsterCharacter.h"

UNotify_MJSpawnTargetProjectile::UNotify_MJSpawnTargetProjectile()
{
}

void UNotify_MJSpawnTargetProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		/*
		 * TODO
		 * 아이템 스폰
		 * 아이템 BP 클래스는 여기서 설정해주면 될듯(변수로 받아서)
		 */
		// Minjin: 스켈레탈의 가운데에서 스폰? 우선 그렇게,,,
		// TODO: Get Bone Location by Name 알아보기
		// FTransform SpawnTransform(MeshComp->GetSkeletalCenterOfMass());

		// 클래스 정보 가져와야 됨.(EnemyBequest 접근 위함)
		AActor* OwnerActor = MeshComp->GetOwner();
		if (OwnerActor == nullptr)
		{
			// Minjin: Actor로 사용한다면 수정하면 될 것 같슴니다.
			return;
		}

		// Minjin: PlayerCharacter
		AMJPlayerCharacter* Player = Cast<AMJPlayerCharacter>(OwnerActor);
		if (Player)
		{
			// Minjin: 필요할진 모르겠지만 놔둬봅니다.
			if (TargetingProjectile)
			{
				FVector SpawnLocation = Player->GetActorLocation();
				SpawnLocation.Z = 0.0f;
				FTransform SpawnTransform(SpawnLocation);
				AMJTargetingProjectileBase* Projectile = Player->GetWorld()->SpawnActorDeferred<AMJTargetingProjectileBase>(TargetingProjectile, SpawnTransform/*, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn*/);
				MJ_LOG(LogMJ, Warning, TEXT("Create TargetProjectile"));
	
				Projectile->FinishSpawning(SpawnTransform);
			}
		}

		AMJMonsterCharacter* Enemy = Cast<AMJMonsterCharacter>(OwnerActor);
		if (Enemy)
		{
			if (TargetingProjectile)
			{
				if (Enemy->GetEnemyBequest().Target == nullptr)
				{
					MJ_LOG(LogMJ, Warning, TEXT("Target is nullptr"));
					return;
				}
				if (!Enemy->GetEnemyBequest().IdentitySkillTag.IsValid())
				{
					MJ_LOG(LogMJ, Warning, TEXT("SkillTage is not valid"));
					return;
				}
				FVector SpawnLocation = Enemy->GetActorLocation();
				SpawnLocation.Z = 0.0f;
				FTransform SpawnTransform(SpawnLocation);
				AMJTargetingProjectileBase* Projectile = Enemy->GetWorld()->SpawnActorDeferred<AMJTargetingProjectileBase>(TargetingProjectile, SpawnTransform/*, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn*/);
				MJ_LOG(LogMJ, Warning, TEXT("Create TargetProjectile"));
				
				Projectile->SetTarget(Enemy->GetEnemyBequest().Target);
				Projectile->SetSkillTag(Enemy->GetEnemyBequest().IdentitySkillTag);

				Projectile->FinishSpawning(SpawnTransform);
			}
		}
	}
}
