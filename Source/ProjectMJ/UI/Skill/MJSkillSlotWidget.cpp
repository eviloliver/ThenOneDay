// ThenOneDayStudio


#include "UI/Skill/MJSkillSlotWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMJSkillSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	HideImage->SetVisibility(ESlateVisibility::Visible);
	Equip->SetIsEnabled(false);
	Equip->OnClicked.AddDynamic(this, &ThisClass::OnClicked_EquipButton);
}

void UMJSkillSlotWidget::SetSkillWidget(FGameplayTag Tag,UTexture2D* Image, FText Name, FText Description, ESkillType skilltype, int32 Level)
{
	SetSkillImage(Image);
	SetSkillName(Name);
	SetSkillDescription(Description);
	SetSkillType(skilltype);
	SetSkillLevel(Level);

	HideImage->SetVisibility(ESlateVisibility::Hidden);
	Equip->SetIsEnabled(true);
	SkillTag = Tag;
}

void UMJSkillSlotWidget::SetEquipedSkillTag(FGameplayTag Tag)
{
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

	SkillIcon = Image;
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

void UMJSkillSlotWidget::SetSkillType(ESkillType type)
{
	FText S_Type = StaticEnum<ESkillType>()->GetDisplayNameTextByValue((int64)type);
	
	if (SkillType)
	{
		SkillType->SetText(S_Type);
	}

	Type = type;
}

void UMJSkillSlotWidget::SetSkillLevel(int32 Level)
{
	if (SkillLevel)
	{
		SkillLevel->SetText(FText::AsNumber(Level));
	}
}

void UMJSkillSlotWidget::OnClicked_EquipButton()
{
	OnClickedEquipButton.Broadcast(SkillIcon,Type, SkillTag);
}
