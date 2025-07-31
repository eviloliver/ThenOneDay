// ThenOneDayStudio

#include "TG/Actor/MJPortalToNextDungeon.h"

#include "Character/MJPlayerCharacter.h"
#include "Controller/MJPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "TG/Component/MJMiniMapIconMeshComponent.h"
#include "TG/UI/MJDungeonMapWidget.h"
#include "TG/UI/MJGameFlowHUDWidget.h"

AMJPortalToNextDungeon::AMJPortalToNextDungeon()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));

	RootComponent = Mesh;
	SphereCollision->SetupAttachment(Mesh);

	MiniMapIconMesh = CreateDefaultSubobject<UMJMiniMapIconMeshComponent>(TEXT("MiniMapIcon"));
	MiniMapIconMesh->SetupAttachment(Mesh);
}

void AMJPortalToNextDungeon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnOverlap);
	
		
}

void AMJPortalToNextDungeon::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AMJPlayerCharacter* Character = Cast<AMJPlayerCharacter>(OtherActor))
	{
		AMJPlayerController* PC = Character->GetController<AMJPlayerController>();
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
}


