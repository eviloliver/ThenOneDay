// ThenOneDayStudio

#include "TG/Actor/MJPortalToNextDungeon.h"

#include "Controller/MJPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "TG/UI/MJDungeonMapWidget.h"
#include "TG/UI/MJGameFlowHUDWidget.h"

AMJPortalToNextDungeon::AMJPortalToNextDungeon()
{
	// MiniMapIconMesh = CreateDefaultSubobject<UMJMiniMapIconMeshComponent>(TEXT("MiniMapIcon"));
	// MiniMapIconMesh->SetupAttachment(StaticMesh);
	
	// TG : Don`t change this for proper SpawnActor
	SetActorRelativeScale3D(FVector(0.38f,0.2f,0.38f));
}

void AMJPortalToNextDungeon::Execute()
{
	Super::Execute();
	
	AMJPlayerController* PC = Cast<AMJPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (PC)
	{
		PC->StopMovement();
		PC->SetInputMode(FInputModeUIOnly());
		UGameplayStatics::PlaySound2D(GetWorld(),CollisionSFX);
		if (UMJDungeonMapWidget* DungeonMapWidget = PC->GetGameFlowHUD()->GetDungeonMapWidget())
		{
			DungeonMapWidget->SetVisibility(ESlateVisibility::Visible);
			DungeonMapWidget->SetAllVisibility(ESlateVisibility::Visible);
		} 
	}
	
}

void AMJPortalToNextDungeon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	// TG : Don`t change this for proper SpawnActor
	SetActorRelativeScale3D(FVector(0.38f,0.2f,0.38f));
}

void AMJPortalToNextDungeon::BeginPlay()
{
	Super::BeginPlay();
	
}
