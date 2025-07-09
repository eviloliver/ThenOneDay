// Fill out your copyright notice in the Description page of Project Settings.

#include "MJGameInstanceTG.h"

UMJGameInstanceTG::UMJGameInstanceTG()
{
	PlayerSessionData.CurrentDungeonMapNum = -1;

}

void UMJGameInstanceTG::Init()
{
	Super::Init();
}

FMJPlayerSessionData& UMJGameInstanceTG::GetPlayerSessionDataRef() 
{
	return PlayerSessionData;
}

TArray<FMJDungeonSessionData>& UMJGameInstanceTG::GetDungeonSessionDataRef()
{
	return DungeonSessionData;
}
