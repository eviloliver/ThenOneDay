// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/MJItemBase.h"

#include "NavigationSystemTypes.h"
#include "TG/MJGameInstance.h"
#include "UI/Inventory/ItemDataRow.h"
#include "UI/World/MJNameBarWidget.h"
#include "UI/World/MJNameBarWidgetComponent.h"


AMJItemBase::AMJItemBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MJItemBase"));
	SetRootComponent(MeshComp);
	
	NameBarWidgetComp = CreateDefaultSubobject<UMJNameBarWidgetComponent>(TEXT("NameBar"));
	NameBarWidgetComp->SetupAttachment(MeshComp);
}

void AMJItemBase::BeginPlay()
{
	Super::BeginPlay();

	UMJGameInstance* GI = GetWorld()->GetGameInstance<UMJGameInstance>();
	if (!GI || !GI->ItemDataTable)
	{
		return;
	}

	const FItemDataRow* ItemRow = GI->ItemDataTable->FindRow<FItemDataRow>(ItemTag.GetTagName(),TEXT("Find ItemData"));
	
	if (UMJNameBarWidget* NameBar = Cast<UMJNameBarWidget>(NameBarWidgetComp->GetUserWidgetObject()))
	{
		NameBar->SetNameText(ItemRow->ItemID);
	}
}


