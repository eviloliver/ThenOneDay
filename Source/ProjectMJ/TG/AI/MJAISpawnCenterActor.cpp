
#include "TG/AI/MJAISpawnCenterActor.h"

AMJAISpawnCenterActor::AMJAISpawnCenterActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;
	
	
}

