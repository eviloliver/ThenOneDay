// Fill out your copyright notice in the Description page of Project Settings.


#include "MJSaveGame.h"

#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"

UMJSaveGame::UMJSaveGame()
{
}

FCharacterAttributeSaveData& UMJSaveGame::GetAttributeSaveData()
{
	return AttributeSaveData;
}
