// ThenOneDayStudio

#include "TG/Component/MJMiniMapIconMeshComponent.h"

#include "Character/MJPlayerCharacter.h"
#include "MJ/Character/MJMonsterCharacter.h"

UMJMiniMapIconMeshComponent::UMJMiniMapIconMeshComponent()
{

	SetRelativeLocation(FVector(0.0f,0.0f,300.f));

	bVisibleInSceneCaptureOnly = true;
	bCanEverAffectNavigation = false;
	
	// have to do this cuz there`s no parent BP of Enemy. and no need for change icon per enemy
	ConstructorHelpers::FObjectFinder<UStaticMesh> EnemyMesh(TEXT("/Game/TG/StaticMesh/SM_MJSphere.SM_MJSphere"));
	if (EnemyMesh.Succeeded())
	{
		EnemyIcon = EnemyMesh.Object;
	}
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowMesh(TEXT("/Game/TG/StaticMesh/SM_MJArrow.SM_MJArrow"));
	if (ArrowMesh.Succeeded())
	{
		PlayerIcon = ArrowMesh.Object;
	}

}

void UMJMiniMapIconMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	
	SetUsingAbsoluteRotation(true);
	SetUsingAbsoluteScale(true);
	SetRelativeRotation(FRotator(0.0f,90.0f,0.0f));	
	SetRelativeLocation(FVector(0.0f,0.0f,300.f));
	SetWorldScale3D(FVector(2.0f,2.0f,1.0f));
	
	SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	SetVisibleInSceneCaptureOnly(true);

	if (AMJMonsterCharacter* MonsterCharacter = Cast<AMJMonsterCharacter>(GetOwner()))
	{
		SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));
		SetRelativeLocation(FVector(0.0f,0.0f,0.f));
		SetStaticMesh(EnemyIcon);
	}
	else if (AMJPlayerCharacter* Player = Cast<AMJPlayerCharacter>(GetOwner()))
	{
		
		SetUsingAbsoluteRotation(false);
		SetUsingAbsoluteScale(false);
		SetRelativeRotation(FRotator(0.0f,0.0f,0.0f));	
		SetStaticMesh(PlayerIcon);
	}
}
