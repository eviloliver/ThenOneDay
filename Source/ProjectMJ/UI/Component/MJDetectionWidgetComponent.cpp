// ThenOneDayStudio


#include "UI/Component/MJDetectionWidgetComponent.h"
#include "UI/World/MJDetectionWidget.h"

UMJDetectionWidgetComponent::UMJDetectionWidgetComponent()
{
	static ConstructorHelpers::FClassFinder<UMJDetectionWidget> DetectionWidgetRef(TEXT("/Game/UI/WBP/Tutorial/WBP_Detection.WBP_Detection_C"));

	if (DetectionWidgetRef.Class)
	{
		SetWidgetClass(DetectionWidgetRef.Class);
	}

	SetDetectionWidget();
}

void UMJDetectionWidgetComponent::SetDetectionWidget()
{
	SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawSize(FVector2D(10.0f,10.0f));
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetVisibility(false);
}
