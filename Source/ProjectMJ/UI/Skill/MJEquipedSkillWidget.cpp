// ThenOneDayStudio


#include "UI/Skill/MJEquipedSkillWidget.h"
#include "Components/Image.h"

void UMJEquipedSkillWidget::SetInstantImage(UTexture2D* ItemTexture)
{
	if (InstantImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(ItemTexture);
		//Brush.ImageSize = FVector2D(80,80);
		InstantImage->SetBrush(Brush);
		InstantImage->SetOpacity(1.0);
	}
}

void UMJEquipedSkillWidget::SetChargingImage(UTexture2D* ItemTexture)
{
	if (ChargingImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(ItemTexture);
		//Brush.ImageSize = FVector2D(80,80);
		ChargingImage->SetBrush(Brush);
		ChargingImage->SetOpacity(1.0);
	}
}

void UMJEquipedSkillWidget::SetPassiveImage(UTexture2D* ItemTexture)
{
	if (PassiveImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(ItemTexture);
		//Brush.ImageSize = FVector2D(80,80);
		PassiveImage->SetBrush(Brush);
		PassiveImage->SetOpacity(1.0);
	}
}
