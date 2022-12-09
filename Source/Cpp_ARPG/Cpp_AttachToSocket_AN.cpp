// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_AttachToSocket_AN.h"

#include "Engine.h"

void UCpp_AttachToSocket_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//CustomRecievedNotify(MeshComp, Animation, bAttachToHandSocket);

	OnRecievedNotify_Delegate.Broadcast(bAttachToHandSocket);

//	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Green, __FUNCTION__);

}
