// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_AC_WeaponSystem.h"
#include "Cpp_AttachToSocket_AN.h"
//#include "Misc/CoreDelegates.h"
#include "AnimBP_Interface.h"

// Sets default values for this component's properties
UCpp_AC_WeaponSystem::UCpp_AC_WeaponSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

// Component setup

	SMC_LeftWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWeaponComponent"));
	SMC_RightWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWeaponComponent"));

	bIsWeaponDrawn = false;
		
}


// Called when the game starts
void UCpp_AC_WeaponSystem::BeginPlay()
{
	Super::BeginPlay();

	// Set the anim Montage based on the weapon equiped
	ownerCastedAsCharacter = Cast<ACharacter>(GetOwner());

	ownersCharacterMesh = ownerCastedAsCharacter->GetMesh();

	// Attach the weapons to the parent
	
	if (ownersCharacterMesh != nullptr)
	{
		SMC_RightWeapon->AttachToComponent(ownersCharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, R_WeaponHolsterSocket_Name);
		SMC_LeftWeapon->AttachToComponent(ownersCharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, L_WeaponHolsterSocket_Name);
	}
	else
	{
		SMC_LeftWeapon->AttachTo(GetOwner()->GetRootComponent());
	}

	SMC_LeftWeapon->SetRelativeLocation(FVector(0, 0, 0));
	SMC_LeftWeapon->SetRelativeRotation(FRotator(0, 0, 0));
	SMC_LeftWeapon->SetRelativeScale3D(FVector(1, 1, 1));

	SMC_RightWeapon->SetStaticMesh(RightWeapon_SM);
	SMC_LeftWeapon->SetStaticMesh(LeftWeapon_SM);

	// Bind inputs for the actions
	BindInput();

}

void UCpp_AC_WeaponSystem::BindInput()
{
	if (GetOwner()->InputComponent)
	{
		// Set up gameplay key bindings

		// Sheath / Draw weapon
		if (weaponSheathDrawInputName != NAME_None)
		{
			GetOwner()->InputComponent->BindAction(weaponSheathDrawInputName, IE_Pressed, this, &UCpp_AC_WeaponSystem::DrawSheatheWeapon);
		}

		// Light Attack
		if (weaponLightAttackInputName != NAME_None)
		{
			GetOwner()->InputComponent->BindAction(weaponLightAttackInputName, IE_Pressed, this, &UCpp_AC_WeaponSystem::WeaponLightAttack);
		}
		
	}
}


// Called every frame
void UCpp_AC_WeaponSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// Draw / Sheath weapon
void UCpp_AC_WeaponSystem::DrawSheatheWeapon()
{
	
	// Check if the owner is a character so we can play an anim montage on it
	if (ownerCastedAsCharacter)
	{
		if (bIsWeaponDrawn)
		{
			ownerCastedAsCharacter->PlayAnimMontage(SheatheWeapon_AM, 1, NAME_None);
			for (int i = 0; i < SheatheWeapon_AM->Notifies.Num(); i++)
			{
//				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, DrawWeapon_AM->Notifies[i].GetNotifyEventName().ToString());
				if (SheatheWeapon_AM->Notifies[i].NotifyName.ToString() == "Cpp_AttachToSocket_AN")
				{

//					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, SheatheWeapon_AM->Notifies[i].NotifyName.ToString());

					UCpp_AttachToSocket_AN* currentNotify = Cast<UCpp_AttachToSocket_AN>(SheatheWeapon_AM->Notifies[i].Notify);
					if (currentNotify != nullptr)
					{
						// Execute the function AN_AttachToSocket when the notify is called
						currentNotify->OnRecievedNotify_Delegate.AddUniqueDynamic(this, &UCpp_AC_WeaponSystem::AN_AttachToSocket);
//						GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, "Linked the Delegate to the Notify.");
					}

				}
			}

		}
		else if (bIsWeaponDrawn == false)
		{
			ownerCastedAsCharacter->PlayAnimMontage(DrawWeapon_AM, 1, NAME_None);
		
			for (int i = 0; i < DrawWeapon_AM->Notifies.Num(); i++)
			{
//				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, DrawWeapon_AM->Notifies[i].GetNotifyEventName().ToString());
				if (DrawWeapon_AM->Notifies[i].NotifyName.ToString() == "Cpp_AttachToSocket_AN")
				{

//					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, DrawWeapon_AM->Notifies[i].NotifyName.ToString());
				
					UCpp_AttachToSocket_AN* currentNotify = Cast<UCpp_AttachToSocket_AN>(DrawWeapon_AM->Notifies[i].Notify);
					if (currentNotify != nullptr)
					{
						// Execute the function AN_AttachToSocket when the notify is called
						currentNotify->OnRecievedNotify_Delegate.AddUniqueDynamic(this, &UCpp_AC_WeaponSystem::AN_AttachToSocket);
//						GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, "Linked the Delegate to the Notify.");
					}

				}
			}
		}
		
	}

}

void UCpp_AC_WeaponSystem::WeaponLightAttack()
{
	// Check if the owner is a character so we can play an anim montage on it
	if (ownerCastedAsCharacter)
	{
		if (bIsWeaponDrawn)
		{
			// Check if there are any AnimMontage in the array
			if (LightAttacks_AM.Num() > 0)
			{
				ownerCastedAsCharacter->PlayAnimMontage(LightAttacks_AM[currentComboCounter], 1, NAME_None);

				for (int i = 0; i < LightAttacks_AM[currentComboCounter]->Notifies.Num(); i++)
				{
					if (LightAttacks_AM[currentComboCounter]->Notifies[i].NotifyName.ToString() == "Cpp_EnableAttackCollision_ANS")
					{
						UCpp_EnableAttackCollision_ANS* currentNotify = Cast<UCpp_EnableAttackCollision_ANS>(LightAttacks_AM[currentComboCounter]->Notifies[i].NotifyStateClass);
						if (currentNotify != nullptr)
						{
							currentNotify->OnNotifyBegin_Delegate.AddDynamic(this, &UCpp_AC_WeaponSystem::ANS_EnableWeaponCollision);
							currentNotify->OnNotifyEnd_Delegate.AddDynamic(this, &UCpp_AC_WeaponSystem::ANS_DisableWeaponCollision);
						}
					}

				}

				// TODO: When the Anim Montage Stops playing, remove the notify delegates, or they will be added to the ones before,
					// stacking indefinetly.

			}
		}
		else
		{
			DrawSheatheWeapon();
		}
	}
}

// Check the state of the weapon
bool UCpp_AC_WeaponSystem::IsWeaponDrawn()
{
	return bIsWeaponDrawn;
}

void UCpp_AC_WeaponSystem::AN_AttachToSocket(bool bAttachedToHandSocket)
{
	// Check if the owner is a character so we can play an anim montage on it

	if (ownerCastedAsCharacter)
	{
		if (bAttachedToHandSocket == false)
		{
			SMC_RightWeapon->AttachToComponent(ownersCharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, R_WeaponHolsterSocket_Name);
			SMC_LeftWeapon->AttachToComponent(ownersCharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, L_WeaponHolsterSocket_Name);
			
			bIsWeaponDrawn = false;

			// Camera behaviour
			ownerCastedAsCharacter->bUseControllerRotationYaw = false;

		}
		else if (bAttachedToHandSocket == true)
		{
			SMC_RightWeapon->AttachToComponent(ownersCharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, R_WeaponHandSocket_Name);
			SMC_LeftWeapon->AttachToComponent(ownersCharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, L_WeaponHandSocket_Name);
						
			bIsWeaponDrawn = true;

			// Camera behaviour
			ownerCastedAsCharacter->bUseControllerRotationYaw = true;
		}

		if (ownersCharacterMesh->GetAnimInstance()->GetClass()->ImplementsInterface(UAnimBP_Interface::StaticClass()))
		{
			// Update the variable on the animInstance via interface call
			IAnimBP_Interface::Execute_SetIsWeaponDrawn(ownersCharacterMesh->GetAnimInstance(), bIsWeaponDrawn);
		}
	}

//	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Blue, __FUNCTION__);
}

void UCpp_AC_WeaponSystem::ANS_EnableWeaponCollision(EWeaponCollisionToActivate::EActivateWeaponCollisions activeWeapons)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
}

void UCpp_AC_WeaponSystem::ANS_DisableWeaponCollision(EWeaponCollisionToActivate::EActivateWeaponCollisions activeWeapons)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
}