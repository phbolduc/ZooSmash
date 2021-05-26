// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZooSmashGameMode.h"
#include "ZooSmashCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZooSmashGameMode::AZooSmashGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ElephantCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
