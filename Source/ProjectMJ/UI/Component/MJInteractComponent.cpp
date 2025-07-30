// ThenOneDayStudio


#include "UI/Component/MJInteractComponent.h"

#include "LandscapeGizmoActiveActor.h"
#include "Dialogue/MJDialogueComponent.h"
#include "UI/Store/MJStoreComponent.h"
#include "UI/World/MJInteractionComponent.h"

// Sets default values for this component's properties


UMJInteractComponent::UMJInteractComponent()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MetarialRef(TEXT("/Game/UI/WBP/HUD/Inventory/woodcover.woodcover"));
	if (MetarialRef.Succeeded())
	{
		OverlayMaterial = MetarialRef.Object;
	}

	WidgetComponent = CreateDefaultSubobject<UMJInteractionComponent>(TEXT("InteractionWidget"));
}

void UMJInteractComponent::OnBeginInteract()
{
	if (UMeshComponent* Mesh = GetOwner()->FindComponentByClass<UMeshComponent>())
	{
		Mesh->SetOverlayMaterial(OverlayMaterial);
		if (WidgetComponent)
		{
			WidgetComponent->AttachToComponent(Mesh,FAttachmentTransformRules::KeepRelativeTransform);
			WidgetComponent->Active("Test");
		}
	}
	EvaluateType();
}

void UMJInteractComponent::OnEndInteract()
{
	if (UMeshComponent* Mesh = GetOwner()->FindComponentByClass<UMeshComponent>())
	{
		Mesh->SetOverlayMaterial(nullptr);
		WidgetComponent->Deactive();
	}
}

void UMJInteractComponent::EvaluateType()
{
	CurrentType = EMJInteractionType::None;

	for (UActorComponent* Comp : GetOwner()->GetComponents())
    {
    	if (Cast<UMJDialogueComponent>(Comp))
    	{
    		DialogueComponent = Cast<UMJDialogueComponent>(Comp);
    		CurrentType = EMJInteractionType::Dialogue;
    		return;
    	}
    	if (Cast<UMJStoreComponent>(Comp))
    	{
    		StoreComponent = Cast<UMJStoreComponent>(Comp);
    		CurrentType = EMJInteractionType::Store;
    		return;
    	}
    }
}


void UMJInteractComponent::StartInteraction()
{
	if (CurrentType == EMJInteractionType::Dialogue)
	{
		DialogueComponent->FloatLine();
		return;
	}
	if (CurrentType == EMJInteractionType::Store)
	{
		StoreComponent->UpdateStore();
		return;
	}
}

void UMJInteractComponent::ProceedInteraction()
{
	if (CurrentType == EMJInteractionType::Dialogue)
	{
		DialogueComponent->TurnOver();
		if (DialogueComponent->IsDialogueEnd())
		{
			DialogueComponent->SetIndex(0);
			OndialogueEnd.Broadcast();
		}
	}
	
	if (CurrentType == EMJInteractionType::Store)
	{
		OnstoreEnd.Broadcast();
	}
}




