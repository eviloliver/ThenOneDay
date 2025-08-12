// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJSkillSlotWidget.generated.h"

class UButton;
/**
 * 
 */
class UTextBlock;
class UImage;

UCLASS()
class PROJECTMJ_API UMJSkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> SkillImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillName;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillDescription;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillType;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> HideImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Equip;

public:
	void SetSkillWidget(UTexture2D* Image,FText Name,FText Description, FText Type,int32 Level);
	
	void SetSkillImage(UTexture2D* Image);
	void SetSkillName(FText Name);
	void SetSkillDescription(FText Description);
	void SetSkillType(FText Type);
	void SetSkillLevel(int32 Level);
};