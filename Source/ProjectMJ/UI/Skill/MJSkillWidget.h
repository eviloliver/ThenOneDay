// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJSkillWidget.generated.h"

/**
* Class Description: 스킬창
 * Author: 이지수
 * Created Date: 2025.08.11
 * Last Modified By: 
 * Last Modified Date: 
 */

class UTextBlock;
class UImage;

UCLASS()
class PROJECTMJ_API UMJSkillWidget : public UUserWidget
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

public:
	void SetSkillImage(UTexture2D* Image);
	void SetSkillName(FText Name);
	void SetSkillDescription(FText Description);
	void SetSkillType(FText Type);
	void SetSkillLevel(int32 Level);
};
