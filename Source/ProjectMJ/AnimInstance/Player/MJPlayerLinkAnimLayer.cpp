// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/Player/MJPlayerLinkAnimLayer.h"
#include "AnimInstance/Player/MJPlayerAnimInstance.h"
#include "MJPlayerLinkAnimLayer.h"

UMJPlayerAnimInstance* UMJPlayerLinkAnimLayer::GetPlayerAnimInstance() const
{
    return Cast<UMJPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
