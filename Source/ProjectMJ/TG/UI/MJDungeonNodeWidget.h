// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TG/Struct/MJPlayerSessionDataStruct.h"
#include "MJDungeonNodeWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * Class Description: DungeonNodeWidget
 * Author: Cha Tae Gwan
 * Created Date: 2025_07_29
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025_07_29
 */
UCLASS()
class PROJECTMJ_API UMJDungeonNodeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UImage> NodeImage;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UTextBlock> NodeNum;

	FMJPlayerSessionData LoadedPlayerSessionData;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

};
