// Fill out your copyright notice in the Description page of Project Settings.


#include "MJHttpDownloadManager.h"
#include "HttpModule.h"
#include "ProjectMJ.h"
#include "Interfaces/IHttpResponse.h"

UMJHttpDownloadManager::UMJHttpDownloadManager()
{
	
}

void UMJHttpDownloadManager::FetchGoogleSheetData()
{
	// HTTP Module 가져오기
	FHttpModule* Http = &FHttpModule::Get();

	// HTTP Request 생성
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	// Google Sheets API URL 설정 
	FString GoogleSheetID = TEXT("1WDXClQfgWQ1tyuY-ieqs5fxcnd_F1sm9Qm7FHW-FbNo"); 
	FString GoogleSheetRange = TEXT("Data"); // 시트 이름 & 범위
	FString ApiKey = TEXT("AIzaSyD2yl3uaq1kzT7YM6hfna62I_Fuw5KLsf8"); 
	FString Url = FString::Printf(TEXT("https://sheets.googleapis.com/v4/spreadsheets/%s/values/%s?key=%s"), *GoogleSheetID, *GoogleSheetRange, *ApiKey); 

	Request->SetURL(Url);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	// Request 완료 시 콜백 설정
	Request->OnProcessRequestComplete().BindUObject(this, &UMJHttpDownloadManager::OnResponseReceived);

	// Request 실행
	Request->ProcessRequest();

	MJ_LOG(LogTGJSON, Log, TEXT("UMJHttpDownloadManager Fetching Google Sheet Data"));
	
}

void UMJHttpDownloadManager::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    MJ_LOG(LogTGJSON, Log, TEXT("UMJHttpDownloadManager OnResponseReceived start"));
	
    if (bWasSuccessful && Response.IsValid())
    {
        MJ_LOG(LogTGJSON, Log, TEXT("UMJHttpDownloadManager OnResponseReceived valid"));
    	
    	FString ResponseString = Response->GetContentAsString();
    	MJ_LOG(LogTemp, Warning, TEXT("==== Raw JSON START ===="));
    	for (int32 i = 0; i < ResponseString.Len(); i += 512)
    	{
    		FString Chunk = ResponseString.Mid(i, 512);
    		MJ_LOG(LogTemp, Warning, TEXT("%s"), *Chunk);
    	}
    	MJ_LOG(LogTemp, Warning, TEXT("==== Raw JSON END ===="));



        // JSON 파싱
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);

        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            MJ_LOG(LogTGJSON, Log, TEXT("UMJHttpDownloadManager OnResponseReceived deserialized"));
            const TArray<TSharedPtr<FJsonValue>>* Rows;

            if (JsonObject->TryGetArrayField(TEXT("values"), Rows))
            {

                MJ_LOG(LogTGJSON, Log, TEXT("UMJHttpDownloadManager getarrayfield"));
            	
                for (const TSharedPtr<FJsonValue>& RowValue : *Rows)
                {
                    const TArray<TSharedPtr<FJsonValue>>& Row = RowValue->AsArray();
                    if (Row.Num() == 2)
                    {
                        FString Key = Row[0]->AsString();
                        float Value = FCString::Atof(*Row[1]->AsString());

                        DataMap.Add(Key, Value);

                        MJ_LOG(LogTGJSON, Log, TEXT("UMJHttpDownloadManager DataMap added: %s - %f"), *Key, Value);
                    }
                }

                // 데이터 로그 출력
                for (const TPair<FString, float>& Pair : DataMap)
                {
                    MJ_LOG(LogTGJSON, Log, TEXT("%s: %f"), *Pair.Key, Pair.Value);
                }

                OnDataFetched.Broadcast();
            }
        }
        else
        {
            MJ_LOG(LogTGJSON, Error, TEXT("Failed to deserialize JSON response"));
        }
    }
    else
    {
        MJ_LOG(LogTGJSON, Error, TEXT("Failed to fetch Google Sheet data"));
    }

}
