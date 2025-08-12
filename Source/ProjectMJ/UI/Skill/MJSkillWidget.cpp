// ThenOneDayStudio


#include "UI/Skill/MJSkillWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMJSkillWidget::SetSkillImage(UTexture2D* Image)
{
	if (SkillImage)
	{
		FSlateBrush Brush;
        Brush.SetResourceObject(SkillImage);
        SkillImage->SetBrush(Brush);
        SkillImage->SetOpacity(1.0);
	}
}

void UMJSkillWidget::SetSkillName(FText Name)
{
	if (SkillDescription)
	{
		SkillDescription->SetText(Name);
	}
	
}

void UMJSkillWidget::SetSkillDescription(FText Description)
{
	if (SkillDescription)
	{
		SkillDescription->SetText(Description);
	}

}

void UMJSkillWidget::SetSkillType(FText Type)
{
	if (SkillType)
	{
		SkillType->SetText(Type);
	}
	
}

void UMJSkillWidget::SetSkillLevel(int32 Level)
{
	if (SkillLevel)
	{
		SkillLevel->SetText(FText::AsNumber(Level));
	}
}
