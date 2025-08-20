// ThenOneDayStudio


#include "UI/Tutorial/MJTutorialInstruction.h"

#include "Components/TextBlock.h"

void UMJTutorialInstruction::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnim();
}

void UMJTutorialInstruction::PlayAnim()
{
	if (InstructionAnim)
	{
		PlayAnimation(InstructionAnim,0.0f, 0);
	}
}

void UMJTutorialInstruction::SetInstructionText(const FString& InInstruction)
{
	if (InstructionText)
	{
		InstructionText->SetText(FText::FromString(InInstruction));
	}
}
