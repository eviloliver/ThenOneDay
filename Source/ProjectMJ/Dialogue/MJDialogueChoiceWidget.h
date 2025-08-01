// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJDialogueChoiceWidget.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJDialogueChoiceWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Quest;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Point;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Exit;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuestButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PointButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

public:
	virtual void NativeConstruct() override;
	
	void SetTextBlock(const FString& quest, const FString& point, const FString& exit);
	
	// Getter
	UButton* GetQuestButton() {return QuestButton;};
	UButton* GetPointButton(){return PointButton;};
	UButton* GetExitButton() {return ExitButton;};
};
