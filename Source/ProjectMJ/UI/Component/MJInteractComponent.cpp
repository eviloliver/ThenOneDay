// ThenOneDayStudio

#include "UI/Component/MJInteractComponent.h"

#include "Dialogue/MJDialogueChoiceWidget.h"
#include "Dialogue/MJDialogueComponent.h"
#include "Dialogue/MJDialogueWidget.h"
#include "TG/Actor/MJSavePointActor.h"
#include "UI/Store/MJStoreComponent.h"
#include "UI/World/MJInteractionComponent.h"

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
			WidgetComponent->Active("F");
		}
	}
	
	EvaluateType();
	
	if (StoreComponent)
	{
		StoreComponent->BindButtons();
	}
	
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
		if (Cast<UMJStoreComponent>(Comp))
         {
         	StoreComponent = Cast<UMJStoreComponent>(Comp);
         	CurrentType = EMJInteractionType::Store;
         	UE_LOG(LogTemp,Error,TEXT("%hhd"),CurrentType);
         	return;
         }
		
    	if (Cast<UMJDialogueComponent>(Comp))
    	{
    		DialogueComponent = Cast<UMJDialogueComponent>(Comp);
    		CurrentType = EMJInteractionType::Dialogue;
    		UE_LOG(LogTemp,Error,TEXT("%hhd"),CurrentType);
    		return;
    	}
		// CTG : add Interact Logic 25.08.05
		if (GetOwner()->IsA(AMJInteractableActor::StaticClass()))
		{
			CurrentType = EMJInteractionType::Interactable;
			return;
		}
    }
}


void UMJInteractComponent::StartInteraction()
{
	// execute logic
	if (CurrentType == EMJInteractionType::Dialogue)
	{
		DialogueComponent->FloatLine();
		return;
	}
	else if (CurrentType == EMJInteractionType::Store)
	{
		StoreComponent->FloatLine();
		StoreComponent->GetDialogueWidget()->GetDialogueChoiceWidget()->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	else if (CurrentType == EMJInteractionType::Interactable)
	{
		if (AMJInteractableActor* Interactable = Cast<AMJInteractableActor>(GetOwner()))
		{
			Interactable->Execute();
		}
	}
}

void UMJInteractComponent::ProceedInteraction()
{
	// if have any procedure, called.
	if (CurrentType == EMJInteractionType::Dialogue)
	{
		DialogueComponent->TurnOver();
		
		if (DialogueComponent->IsDialogueEnd())
		{
			DialogueComponent->SetIndex(0);
			OndialogueEnd.Broadcast(); // 컨트롤러에서 다이어로그 꺼지는 함수 실행될거임
		}
	}
	
	if (CurrentType == EMJInteractionType::Store)
	{
		if (StoreComponent->bIsFirstIndex()) 
		{
			StoreComponent->SkipTyping();
			if (StoreComponent->GetIsOpened()) // 열려있으니까
			{
         		OnstoreClose.Broadcast(); // 닫을거임
         		StoreComponent->SetbIsOpened(false);
         		StoreComponent->SetIndex(0);
         		return;
         	}
			return;
		}
		
		StoreComponent->TurnOver();
		
		if (StoreComponent->IsDialogueEnd())
		{
			if (StoreComponent->GetIsStoreRoot())
			{
				StoreComponent->DialogueEnd();// 이 함수안에서 IsOpened true가 되
                StoreComponent->UpdateStore();
                OnstoreOpen.Broadcast(); //컨트롤러에서 다이어로그는 꺼지고, 스토어는 열리는 ui 함수가 호출될거임
				StoreComponent->SetbIsStoreRoot(false);
			}
			else
			{
				StoreComponent->SetIndex(0);
				OndialogueEnd.Broadcast();
			}
			return;
		}
		
    		
	}
}




