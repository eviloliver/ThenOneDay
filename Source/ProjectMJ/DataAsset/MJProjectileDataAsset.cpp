// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/MJProjectileDataAsset.h"

TSubclassOf<AMJProjectileBase> UMJProjectileDataAsset::FindProjectileClassForTag(const FGameplayTag& Tag) const
{
	if (const TSubclassOf<AMJProjectileBase>* FoundClass = ProjectileMap.Find(Tag))
	{
		return *FoundClass;
	}
	return nullptr;
}