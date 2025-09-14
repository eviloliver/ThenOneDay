// ThenOneDayStudio


#include "TG/Actor/MJMiniMapBackgroundActor.h"

AMJMiniMapBackgroundActor::AMJMiniMapBackgroundActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMesh;

	StaticMesh->bCastDynamicShadow = false;
}
