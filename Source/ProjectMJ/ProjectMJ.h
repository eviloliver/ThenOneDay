// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
#define MJ_LOG(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("%s %s"), LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

// cpp 파일에 DEFINE_LOG_CATEGORY 선언 필요함
DECLARE_LOG_CATEGORY_EXTERN(LogMJ, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTG, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTGJSON, Log, All);
