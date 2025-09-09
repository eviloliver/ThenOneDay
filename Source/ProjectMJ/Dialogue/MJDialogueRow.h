#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MJDialogueRow.generated.h"
/**
 * Class Description: DataTable 항목 구조체
 * Author: 이지수
 * Created Date: 2025.06.12
 * Last Modified By: 이지수
 * Last Modified Date: 2025.06.12
 */
USTRUCT(BlueprintType)
struct FDialogueChoice
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ChoiceText; // 버튼으로 업데이트 되어야할 텍스트

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextNodeID; // 다음 노드의 번호, 해당 번호로 Script 변경
};

USTRUCT(BlueprintType)
struct FMJDialogueRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NodeID; // 현재 노드의 번호
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Speaker; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ScriptForStore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ScriptForExit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* PlayerMugImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* NPCMugImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueChoice> Choices; // 선택지는 여러개니까 배열?
};
