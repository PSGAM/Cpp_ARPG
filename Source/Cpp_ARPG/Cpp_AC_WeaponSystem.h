// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Cpp_EnableAttackCollision_ANS.h"
#include "Cpp_AC_WeaponSystem.generated.h" 

/*
* Design intention:
* Encapsulating all the implementation needed in a weapon system (Draw/Sheath, Attack, Block...)
*	assuming that we don't have access to the player's character because it's blocked by another
*	developer.
* 
* Intentionally avoiding any blueprint exposure to force myself the interaction in C++ as much
*	as possible. Binding input and calling the actions will normally be on the BP.
*/


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class CPP_ARPG_API UCpp_AC_WeaponSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCpp_AC_WeaponSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Bind all the neccesary inputs from the player controller
	void BindInput();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "WeaponActions")
	void DrawSheatheWeapon();

	UFUNCTION(BlueprintCallable, Category = "WeaponActions")
	void WeaponLightAttack();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "")
	bool IsWeaponDrawn();

	// Function called from an animNotify
	UFUNCTION(BlueprintCallable, Category = "")
	void AN_AttachToSocket(bool bAttachedToHandSocket);

	UFUNCTION(BlueprintCallable, Category = "")
	void ANS_EnableWeaponCollision(EWeaponCollisionToActivate::EActivateWeaponCollisions activeWeapons);

	UFUNCTION(BlueprintCallable, Category = "")
	void ANS_DisableWeaponCollision(EWeaponCollisionToActivate::EActivateWeaponCollisions activeWeapons);
		
	// Variables
public:

	// Seath / Draw weapon
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponVariables|InputNames")
	FName weaponSheathDrawInputName = NAME_None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimMontages")
	class UAnimMontage* DrawWeapon_AM = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimMontages")
	class UAnimMontage* SheatheWeapon_AM = nullptr;

	
	// Light Attack
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponVariables|InputNames")
	FName weaponLightAttackInputName = NAME_None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimMontages")
	TArray<UAnimMontage*> LightAttacks_AM;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponVariables|SocketNames")
	FName R_WeaponHolsterSocket_Name = NAME_None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponVariables|SocketNames")
	FName L_WeaponHolsterSocket_Name = NAME_None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponVariables|SocketNames")
	FName R_WeaponHandSocket_Name = NAME_None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponVariables|SocketNames")
	FName L_WeaponHandSocket_Name = NAME_None;
		
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponVariables|StaticMesh")
	class UStaticMesh* RightWeapon_SM = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponVariables|StaticMesh")
	class UStaticMesh* LeftWeapon_SM = nullptr;
	
protected:
	bool bIsWeaponDrawn;
	
	class UStaticMeshComponent* SMC_RightWeapon = nullptr;

	class UStaticMeshComponent* SMC_LeftWeapon = nullptr;

	class ACharacter* ownerCastedAsCharacter = nullptr;

	class USkeletalMeshComponent* ownersCharacterMesh = nullptr;

	int currentComboCounter = 0;

};
