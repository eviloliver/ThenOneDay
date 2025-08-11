// ThenOneDayStudio

#include "TG/Actor/MJInteractableActor.h"

#include "Components/SphereComponent.h"
#include "TG/Component/MJMiniMapIconMeshComponent.h"
#include "UI/Component/MJInteractComponent.h"

AMJInteractableActor::AMJInteractableActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereCollision->SetupAttachment(StaticMesh);

	InteractComponent = CreateDefaultSubobject<UMJInteractComponent>(TEXT("InteractComp"));

	MiniMapIconMesh = CreateDefaultSubobject<UMJMiniMapIconMeshComponent>(TEXT("MiniMapIconMesh"));
	MiniMapIconMesh->SetupAttachment(StaticMesh);
	
}

void AMJInteractableActor::Execute()
{
	
}



