// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_EnableAttackCollision_ANS.h"

void UCpp_EnableAttackCollision_ANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	OnNotifyBegin_Delegate.Broadcast(activeWeapons);
}

void UCpp_EnableAttackCollision_ANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	OnNotifyTick_Delegate.Broadcast(activeWeapons);
}

void UCpp_EnableAttackCollision_ANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifyEnd_Delegate.Broadcast(activeWeapons);
}