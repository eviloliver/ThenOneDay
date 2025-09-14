// ThenOneDayStudio


#include "UI/World/MJNameBarWidgetComponent.h"
#include "MJNameBarWidget.h"

UMJNameBarWidgetComponent::UMJNameBarWidgetComponent()
{
	static ConstructorHelpers::FClassFinder<UMJNameBarWidget> NameBarWidgetRef(TEXT("/Game/UI/WBP/World/WBP_ItemNameBar.WBP_ItemNameBar_C"));

	if (NameBarWidgetRef.Class)
	{
		SetWidgetClass(NameBarWidgetRef.Class);
	}

	SetNameBarWidget();
}

void UMJNameBarWidgetComponent::SetNameBarWidget()
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	SetDrawSize({100,40});
}
