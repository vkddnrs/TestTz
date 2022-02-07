// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTzGameMode.h"
#include "TestTzCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestTzGameMode::ATestTzGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
