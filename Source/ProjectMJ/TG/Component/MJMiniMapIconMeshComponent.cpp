// ThenOneDayStudio


#include "TG/Component/MJMiniMapIconMeshComponent.h"

#include "Character/MJPlayerCharacter.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "TG/Actor/MJPortalToNextDungeon.h"

UMJMiniMapIconMeshComponent::UMJMiniMapIconMeshComponent()
{
	SetRelativeLocation(FVector(0.0f,-200.f,160.f));
	SetRelativeRotation(FRotator(0.0f,90.0f,0.0f));
	SetRelativeScale3D(FVector(2.0f,2.0f,1.0f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowMesh(TEXT("/Game/TG/StaticMesh/SM_MJArrow.SM_MJArrow"));
	if (ArrowMesh.Succeeded())
	{
		PlayerIcon = ArrowMesh.Object;
	}
	ConstructorHelpers::FObjectFinder<UStaticMesh> EnemyMesh(TEXT("/Game/TG/StaticMesh/SM_MJSphere.SM_MJSphere"));
	if (EnemyMesh.Succeeded())
	{
		EnemyIcon = EnemyMesh.Object;
	}
	ConstructorHelpers::FObjectFinder<UStaticMesh> PortalMesh(TEXT("/Game/TG/StaticMesh/SM_MJPortal.SM_MJPortal"));
	if (PortalMesh.Succeeded())
	{
		PortalIcon = PortalMesh.Object;
	}
}

void UMJMiniMapIconMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	SetVisibleInSceneCaptureOnly(true);

	if (AMJMonsterCharacter* MonsterCharacter = Cast<AMJMonsterCharacter>(GetOwner()))
	{
		SetRelativeLocation(FVector(0.0f,0.f,0.f));
		SetRelativeRotation(FRotator(0.0f,90.0f,0.0f));
		SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));
		SetStaticMesh(EnemyIcon);
	}
	else if (AMJPortalToNextDungeon* PortalToNextDungeon = Cast<AMJPortalToNextDungeon>(GetOwner()))
	{
		SetRelativeLocation(FVector(0.0f,0.f,0.f));
		SetRelativeRotation(FRotator(0.0f,90.0f,0.0f));
		SetRelativeScale3D(FVector( 2.0f,2.0f,2.0f));
		
		SetStaticMesh(PortalIcon);
	}
	else if (AMJPlayerCharacter* Player = Cast<AMJPlayerCharacter>(GetOwner()))
	{
		SetStaticMesh(PlayerIcon);
	}
}
