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

struct FGameplayTag;
class UScrollBox;
class UMJSkillSlotWidget;

UCLASS()
class PROJECTMJ_API UMJSkillWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;

	void UpdateSkillSlots(FGameplayTag SkillTag,int32 Level);
protected:
	UPROPERTY(meta = (BindWidget))
	TArray<TObjectPtr<UMJSkillSlotWidget>> SkillSlots;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Skill)
	TSubclassOf<UMJSkillSlotWidget> SkillSlotClass;
	
};
