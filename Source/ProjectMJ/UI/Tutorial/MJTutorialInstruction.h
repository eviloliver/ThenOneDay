// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJTutorialInstruction.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJTutorialInstruction : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidgetAnim),Transient)
	TObjectPtr<UWidgetAnimation> InstructionAnim;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InstructionText;

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void PlayAnim();

	UFUNCTION()
	void SetInstructionText(const FString& InInstruction);
};
