// ThenOneDayStudio


#include "UI/Skill/MJSkillWidget.h"

#include "GameplayTagContainer.h"
#include "MJSkillSlotWidget.h"
#include "Components/ScrollBox.h"
#include "DataTable/MJSkillDataRow.h"
#include "TG/MJGameInstanceTG.h"


void UMJSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!SkillSlotClass)
	{
		return;
	}
	for (int j = 0; j < 10; ++j)
	{
		UMJSkillSlotWidget* NewSlot = CreateWidget<UMJSkillSlotWidget>(this, SkillSlotClass);
		ScrollBox->AddChild(NewSlot);
		SkillSlots.Add(NewSlot);
	}
}

void UMJSkillWidget::UpdateSkillSlots(FGameplayTag SkillTag,int32 Level)
{
	UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
	if (!GI ||!GI->PlayerSkillDataTable)
	{
		return;
	}
	
	const FMJSkillDataRow* Row = GI->PlayerSkillDataTable->FindRow<FMJSkillDataRow>(SkillTag.GetTagName(),TEXT(""));
	if (!Row)
	{
		return;
	}
	
	int32 Index = Row->SkillIndex;
	UTexture2D* Image = Row->Icon;
	FText Name = Row->SkillName;
	FText Description =Row->SkillDescription;
	ESkillType SkillType =Row->SkillType;
	FText Type = StaticEnum<ESkillType>()->GetDisplayNameTextByValue((int64)SkillType);
	
	SkillSlots[Index]->SetSkillWidget(Image, Name, Description, Type, Level);
	
}
