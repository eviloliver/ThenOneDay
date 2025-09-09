// ThenOneDayStudio


#include "UI/Skill/MJEquipedSkillWidget.h"
#include "TG/MJGameInstance.h"
#include "GameplayTagContainer.h"
#include "Components/Image.h"
#include "DataTable/MJSkillDataRow.h"

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

void UMJEquipedSkillWidget::SetAllImage(FGameplayTag SkillTag)
{
	UMJGameInstance* GI = GetWorld()->GetGameInstance<UMJGameInstance>();
	if (!GI ||!GI->PlayerSkillDataTable)
	{
		return;
	}
	
	const FMJSkillDataRow* Row = GI->PlayerSkillDataTable->FindRow<FMJSkillDataRow>(SkillTag.GetTagName(),TEXT(""));
	if (!Row)
	{
		return;
	}

	if (Row->SkillType == ESkillType::Instant)
	{
		SetInstantImage(Row->Icon);
	}
	if (Row->SkillType == ESkillType::Passive)
	{
		SetPassiveImage(Row->Icon);
	}
	if (Row->SkillType == ESkillType::Charge)
	{
		SetChargingImage(Row->Icon);
	}
}


