// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimBP_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimBP_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CPP_ARPG_API IAnimBP_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon Functions")
	void SetIsWeaponDrawn(bool bIsWeaponDrawn);

};
