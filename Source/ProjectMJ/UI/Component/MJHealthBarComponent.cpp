// ThenOneDayStudio


#include "UI/Component/MJHealthBarComponent.h"

#include "UI/Bar/MJEnemyHPBar.h"

UMJHealthBarComponent::UMJHealthBarComponent()
{
	static ConstructorHelpers::FClassFinder<UMJEnemyHPBar> HealthBarWidgetRef(TEXT("/Game/UI/WBP/World/Bar/WBP_EnemyHPBar.WBP_EnemyHPBar_C"));

	if (HealthBarWidgetRef.Class)
	{
		SetWidgetClass(HealthBarWidgetRef.Class);
	}

	SetHPBarWidget();
}

void UMJHealthBarComponent::SetHPBarWidget()
{
	SetRelativeLocation(FVector(0.0f, 0.0f, 220.0f));
    SetWidgetSpace(EWidgetSpace::Screen);
    SetDrawSize(FVector2D(100.0f,10.0f));
    SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetVisibility(false);
}