// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJStatComponentBase.h"

UMJStatComponentBase::UMJStatComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMJStatComponentBase::OnDead(AActor* InEffectCauser)
{
	// wanna any implemenation, override and call super.
	
	bIsDead = true;
	
	OnDeath.Broadcast(InEffectCauser);
}



