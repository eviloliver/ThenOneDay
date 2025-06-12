// Fill out your copyright notice in the Description page of Project Settings.


#include "MJSaveGame.h"

#include "AbilitySystem/MJCharacterAttributeSet.h"

UMJSaveGame::UMJSaveGame()
{
}

FCharacterAttributeSaveData& UMJSaveGame::GetAttributeSaveData()
{
	return AttributeSaveData;
}
