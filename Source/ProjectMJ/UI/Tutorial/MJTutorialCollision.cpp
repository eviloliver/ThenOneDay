// ThenOneDayStudio


#include "UI/Tutorial/MJTutorialCollision.h"
#include "Components/BoxComponent.h"

// Sets default values
AMJTutorialCollision::AMJTutorialCollision()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TutorialCollision"));
	RootComponent = CollisionBox;
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetHiddenInGame(true);
}

void AMJTutorialCollision::Hide()
{
	Destroy();
}

