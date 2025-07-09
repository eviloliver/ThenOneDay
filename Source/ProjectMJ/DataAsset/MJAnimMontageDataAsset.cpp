// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/MJAnimMontageDataAsset.h"

TObjectPtr<UAnimMontage> UMJAnimMontageDataAsset::FindAnimMontageForTag(const FGameplayTag& Tag) const
{
	if (const TObjectPtr<UAnimMontage>* FoundAnimMontage = AnimMontageMap.Find(Tag))
	{
		return *FoundAnimMontage;
	}
	return nullptr;
}
