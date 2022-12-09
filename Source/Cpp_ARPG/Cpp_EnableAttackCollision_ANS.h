// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Cpp_EnableAttackCollision_ANS.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
namespace EWeaponCollisionToActivate
{
	enum EActivateWeaponCollisions
	{
		BothHands UMETA(DisplayName = "Both hands"),
		LeftHand UMETA(DisplayName = "Left hand"),
		RightHand UMETA(DisplayName = "Right hand"),
	};
}

UCLASS()
class CPP_ARPG_API UCpp_EnableAttackCollision_ANS : public UAnimNotifyState
{
	GENERATED_BODY()	
		
public:
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// Event delegates for the event dispatchers
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FED_OnNotifyBegin_Signature, EWeaponCollisionToActivate::EActivateWeaponCollisions, activeWeapons);
	FED_OnNotifyBegin_Signature OnNotifyBegin_Delegate;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FED_OnNotifyTick_Signature, EWeaponCollisionToActivate::EActivateWeaponCollisions, activeWeapons);
	FED_OnNotifyTick_Signature OnNotifyTick_Delegate;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FED_OnNotifyEnds_Signature, EWeaponCollisionToActivate::EActivateWeaponCollisions, activeWeapons);
	FED_OnNotifyEnds_Signature OnNotifyEnd_Delegate;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "")
	TEnumAsByte<EWeaponCollisionToActivate::EActivateWeaponCollisions> activeWeapons;
	//EWeaponCollisionToActivate::EActivateWeaponCollisions activeWeapons;
};
