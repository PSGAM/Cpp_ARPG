// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Cpp_AttachToSocket_AN.generated.h"

/**
 * 
 */
UCLASS()
class CPP_ARPG_API UCpp_AttachToSocket_AN : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// Event delegate for the event dispatcher
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FED_OnRecievedNotify_Signature, bool, bAttachedToHandSocket);
	FED_OnRecievedNotify_Signature OnRecievedNotify_Delegate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "")
	bool bAttachToHandSocket;
};
