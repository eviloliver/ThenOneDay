// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "MJHttpDownloadManager.generated.h"

/**
 * Class Description: 구글 시트 파싱해서 JSON 으로 가져오는 HttpDownloader
 * Author: 차태관
 * Created Date: 25-06-15
 * Last Modified By: 차태관
 * Last Modified Date: 25-06-15
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDataFetched);

UCLASS()
class PROJECTMJ_API UMJHttpDownloadManager : public UObject
{
	GENERATED_BODY()


public:

	UMJHttpDownloadManager();
	
	UFUNCTION(BlueprintCallable, Category = HTTP)
	void FetchGoogleSheetData();


	UPROPERTY()
	TMap<FString, float> DataMap;

	FOnDataFetched OnDataFetched;

protected:
	
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);



};