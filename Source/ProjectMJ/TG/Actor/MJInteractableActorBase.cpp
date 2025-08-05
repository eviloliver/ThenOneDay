// ThenOneDayStudio

#include "TG/Actor/MJInteractableActorBase.h"

#include "Components/SphereComponent.h"
#include "UI/Component/MJInteractComponent.h"

AMJInteractableActorBase::AMJInteractableActorBase()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereCollision->SetupAttachment(StaticMesh);

	InteractComponent = CreateDefaultSubobject<UMJInteractComponent>(TEXT("InteractComp"));
}

void AMJInteractableActorBase::Execute()
{
	
}



