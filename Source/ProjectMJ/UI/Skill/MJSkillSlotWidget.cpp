// ThenOneDayStudio


#include "UI/Skill/MJSkillSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMJSkillSlotWidget::SetSkillWidget(UTexture2D* Image, FText Name, FText Description, FText Type, int32 Level)
{
	SetSkillImage(Image);
	SetSkillName(Name);
	SetSkillDescription(Description);
	SetSkillType(Type);
	SetSkillLevel(Level);

	HideImage->SetVisibility(ESlateVisibility::Hidden);
}

void UMJSkillSlotWidget::SetSkillImage(UTexture2D* Image)
{
	if (SkillImage)
	{
		FSlateBrush Brush;
        Brush.SetResourceObject(Image);
        SkillImage->SetBrush(Brush);
        SkillImage->SetOpacity(1.0);
	}
}

void UMJSkillSlotWidget::SetSkillName(FText Name)
{
	if (SkillName)
	{
		SkillName->SetText(Name);
	}
}

void UMJSkillSlotWidget::SetSkillDescription(FText Description)
{
	if (SkillDescription)
	{
		SkillDescription->SetText(Description);
	}
}

void UMJSkillSlotWidget::SetSkillType(FText Type)
{
	if (SkillType)
	{
		SkillType->SetText(Type);
	}
}

void UMJSkillSlotWidget::SetSkillLevel(int32 Level)
{
	if (SkillLevel)
	{
		SkillLevel->SetText(FText::AsNumber(Level));
	}
}