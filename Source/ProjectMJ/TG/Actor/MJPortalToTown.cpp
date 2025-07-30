// ThenOneDayStudio


#include "TG/Actor/MJPortalToTown.h"

#include "Components/SphereComponent.h"
#include "GameMode/MJGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AMJPortalToTown::AMJPortalToTown()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(StaticMesh);
	
	

}

void AMJPortalToTown::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AMJPortalToTown::GotoTown);
}

void AMJPortalToTown::GotoTown( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	AGameModeBase* GM = UGameplayStatics::GetGameMode(GetWorld());
	if (IsValid(GM))
	{
		AMJGameModeBase* MJGM = Cast<AMJGameModeBase>(GM);
		if (IsValid(MJGM))
		{
			MJGM->TravelToMap(TEXT("TG_Town"));	
		}
	}
}
