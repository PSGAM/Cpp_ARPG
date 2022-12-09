// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cpp_ARPGGameMode.h"
#include "Cpp_ARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACpp_ARPGGameMode::ACpp_ARPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
