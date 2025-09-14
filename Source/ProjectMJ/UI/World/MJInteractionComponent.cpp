// Fill out your copyright notice in the Description page of Project Settings.


#include "MJInteractionComponent.h"
#include "MJInteractionWidget.h"

UMJInteractionComponent::UMJInteractionComponent()
{
	static ConstructorHelpers::FClassFinder<UMJInteractionWidget> InteractionWidgetRef(TEXT("/Game/UI/WBP/World/WBP_DialogueInteraction.WBP_DialogueInteraction_C"));
 
 	if (InteractionWidgetRef.Class)
 	{
 		SetWidgetClass(InteractionWidgetRef.Class);
 	}
	
	SetInteractionWidget();
}

void UMJInteractionComponent::SetInteractionWidget()
{
	// 기타 세팅
	SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
    SetWidgetSpace(EWidgetSpace::Screen);
    SetDrawSize(FVector2D(80.0f,80.0f));
    SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetVisibility(false);
}

void UMJInteractionComponent::Active(FString key)
{
	SetVisibility(true);
	UMJInteractionWidget* InteractionWidget = Cast<UMJInteractionWidget>(GetUserWidgetObject());
	InteractionWidget->SetText(key);
	InteractionWidget->PlayTestAnimation();
}

void UMJInteractionComponent::Deactive()
{
	SetVisibility(false);
}

